///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-02-2015
///		Date update	: 19-02-2015
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_RESPONSE_H__
#define __DATA_ADAPTER_RESPONSE_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_response
/// ############################################################################
    class data_response
	{
    public:
        enum field_data_response : int
        {
            num_field_object_type = 0,
            num_field_response = 1,
            fields_count = 2
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_response( ) :
            _x_object_type(""),
            _x_response("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_response( const data_response &rhs ) :
            _x_object_type(rhs._x_object_type),
            _x_response(rhs._x_response)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_response( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = row[num_field_object_type].toString( );
            this->_x_response = row[num_field_response].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_response( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = (*p_row)[num_field_object_type].toString( );
            this->_x_response = (*p_row)[num_field_response].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_response( )
		{
            qDebug( ) << "deleted : " << this->_x_object_type << " " +
                                         this->_x_response;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_x_object_type.clear();
            this->_x_response.clear();
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	violation_type
        const QString& object_type( ) const
        { return this->_x_object_type; }

        void object_type( const QString &x_type )
        { this->_x_object_type = x_type; }

    /// ------------------------------------------------------------------------
    ///	description
        const QString& response( ) const
        { return this->_x_response; }

        void response( const QString &x_response )
        { this->_x_response = x_response; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_response& operator=( const data_response &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_x_object_type = rhs._x_object_type;
            this->_x_response = rhs._x_response;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QString _x_object_type; //--тип объекта видеонаблюдения
        QString _x_response;    //--ответственный

    };//class data_response
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_response_collection
/// ############################################################################
    typedef QList<data_response *> list_data_response;
    class data_response_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_response_collection( const data_response_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_response_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_response_collection( )
		{ this->free( ); }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		int size( ) const
		{
			if( !this->_data )
			{
				return 0;
			}
			return this->_data->size( );
		}

    /// ------------------------------------------------------------------------
		void free_data_pointer( )
		{
			if( !this->_data )
			{
				return;
			}
			//free pointer to list
			//but save pointers on list elements
			delete _data;
			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
		void free( )
		{
			if( !this->_data )
			{
				return;
			}
			while( this->_data->size( ) )
			{
				//get last element
                data_response *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_response *r )
		{
			if( !this->_data )
			{
                this->_data = new list_data_response;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        list_data_response* list( )
		{ return this->_data; }
    /// ------------------------------------------------------------------------
        typedef list_data_response::iterator iterator;
    /// ------------------------------------------------------------------------
        iterator begin( )
        {
            return this->_data->begin( );
        }

    /// ------------------------------------------------------------------------
        iterator end( )
        {
            return this->_data->end( );
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_response_collection& operator=(
                                        const data_response_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        list_data_response	*_data;

    };//class data_response_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_response
/// ############################################################################
    class data_adapter_response
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_response( const data_adapter_response &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_response( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_response( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_response &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_response &old_rec,
                                const data_response &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_response &r
                               ) const;
    /// ------------------------------------------------------------------------
        QString make_select_filter(
                                    const QString &s_object_type,
                                    const QString &s_filter
                                  ) const;

    public:
    /// ------------------------------------------------------------------------
        data_response_collection* select( ) const;
    /// ------------------------------------------------------------------------
        data_response_collection* select(
                                            const QString &s_object_type,
                                            const QString &s_filter/*=QString( )*/
                                          ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_response &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_response &old_record,
                    const data_response &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_response &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_response& operator=( const data_adapter_response &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_response

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_RESPONSE_H__
