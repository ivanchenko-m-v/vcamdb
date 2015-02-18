///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-02-2015
///		Date update	: 18-02-2015
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_CONTRACTOR_H__
#define __DATA_ADAPTER_CONTRACTOR_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_contractor
/// ############################################################################
    class data_contractor
	{
    public:
        enum field_data_contractor : int
        {
            num_field_object_type = 0,
            num_field_contractor = 1,
            fields_count = 2
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_contractor( ) :
            _x_object_type(""),
            _x_contractor("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_contractor( const data_contractor &rhs ) :
            _x_object_type(rhs._x_object_type),
            _x_contractor(rhs._x_contractor)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_contractor( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = row[num_field_object_type].toString( );
            this->_x_contractor = row[num_field_contractor].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_contractor( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = (*p_row)[num_field_object_type].toString( );
            this->_x_contractor = (*p_row)[num_field_contractor].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_contractor( )
		{
            qDebug( ) << "deleted : " << this->_x_object_type << " " +
                                         this->_x_contractor;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_x_object_type.clear();
            this->_x_contractor.clear();
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
        const QString& contractor( ) const
        { return this->_x_contractor; }

        void contractor( const QString &x_contractor )
        { this->_x_contractor = x_contractor; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_contractor& operator=( const data_contractor &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_x_object_type = rhs._x_object_type;
            this->_x_contractor = rhs._x_contractor;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QString _x_object_type; //--тип объекта видеонаблюдения
        QString _x_contractor;  //--подрядчик

    };//class data_contractor
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_contractor_collection
/// ############################################################################
    class data_contractor_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_contractor_collection( const data_contractor_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_contractor_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_contractor_collection( )
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
                data_contractor *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_contractor *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_contractor *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_contractor *>* list( )
		{ return this->_data; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_contractor_collection& operator=(
                                        const data_contractor_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_contractor *>	*_data;

    };//class data_contractor_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_contractor
/// ############################################################################
    class data_adapter_contractor
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_contractor( const data_adapter_contractor &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_contractor( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_contractor( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_contractor &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_contractor &old_rec,
                                const data_contractor &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_contractor &r
                               ) const;
    /// ------------------------------------------------------------------------
        QString make_select_filter(
                                    const QString &s_object_type,
                                    const QString &s_filter
                                  ) const;

    public:
    /// ------------------------------------------------------------------------
        data_contractor_collection* select( ) const;
    /// ------------------------------------------------------------------------
        data_contractor_collection* select(
                                            const QString &s_object_type,
                                            const QString &s_filter/*=QString( )*/
                                          ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_contractor &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_contractor &old_record,
                    const data_contractor &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_contractor &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_contractor& operator=( const data_adapter_contractor &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_contractor

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_CONTRACTOR_H__
