///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-10-2014
///		Date update	: 20-02-2015
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_VIOLATION_TYPE_H__
#define __DATA_ADAPTER_VIOLATION_TYPE_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_violation_type
/// ############################################################################
    class data_violation_type
	{
    public:
        enum field_data_violation_type : int
        {
            num_field_object_type = 0,
            num_field_violation_type = 1,
            num_field_status = 2,
            fields_count = 3
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_violation_type( ) :
            _x_object_type(""),
            _x_violation_type(""),
            _n_status(-1)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_type( const data_violation_type &rhs ) :
            _x_object_type(rhs._x_object_type),
            _x_violation_type(rhs._x_violation_type),
            _n_status(rhs._n_status)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_type( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = row[num_field_object_type].toString( );
            this->_x_violation_type = row[num_field_violation_type].toString( );
            this->_n_status = row[num_field_status].toInt( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_type( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_object_type = (*p_row)[num_field_object_type].toString( );
            this->_x_violation_type = (*p_row)[num_field_violation_type].toString( );
            this->_n_status = (*p_row)[num_field_status].toInt( );
        }
    /// ------------------------------------------------------------------------
        ~data_violation_type( )
		{
            qDebug( ) << "deleted : " << this->_x_object_type << " " +
                                         this->_x_violation_type;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_x_object_type.clear( );
            this->_x_violation_type.clear( );
            this->_n_status = -1;
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	object_type
        const QString& object_type( ) const
        { return this->_x_object_type; }

        void object_type( const QString &x_type )
        { this->_x_object_type = x_type; }

    /// ------------------------------------------------------------------------
    ///	violation_type
        const QString& violation_type( ) const
        { return this->_x_violation_type; }

        void violation_type( const QString &x_violation_type )
        { this->_x_violation_type = x_violation_type; }

    /// ------------------------------------------------------------------------
    ///	status
        int status( ) const
        { return this->_n_status; }

        void status( const int n_status )
        { this->_n_status = n_status; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_violation_type& operator=( const data_violation_type &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_x_object_type = rhs._x_object_type;
            this->_x_violation_type = rhs._x_violation_type;
            this->_n_status = rhs._n_status;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QString _x_object_type;       //--тип объекта видеонаблюдения
        QString _x_violation_type;    //--тип нарушения на объекте видеонаблюдения
        int     _n_status;            //--статус типа нарушения

    };//class data_violation_type
/// ############################################################################
/// ----------------------------------------------------------------------------

    typedef QList<data_violation_type *> list_data_violation_type;

/// ############################################################################
///			data_violation_type_collection
/// ############################################################################
    class data_violation_type_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_violation_type_collection( const data_violation_type_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_violation_type_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_violation_type_collection( )
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
                data_violation_type *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_violation_type *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_violation_type *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        list_data_violation_type* list( )
		{ return this->_data; }

    /// ------------------------------------------------------------------------
        typedef list_data_violation_type::iterator iterator;
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
        data_violation_type_collection& operator=(
                                        const data_violation_type_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        list_data_violation_type	*_data;

    };//class data_violation_type_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_violation_type
/// ############################################################################
    class data_adapter_violation_type
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_violation_type( const data_adapter_violation_type &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_violation_type( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_violation_type( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_type &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_type &old_rec,
                                const data_violation_type &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_type &r
                               ) const;

    ///------------------------------------------------------------------------
        QString make_select_filter( const QString &s_object_type ) const;

    public:
    /// ------------------------------------------------------------------------
        data_violation_type_collection* select( ) const;
    /// ------------------------------------------------------------------------
        data_violation_type_collection* select( const QString &s_object_type ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_violation_type &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_violation_type &old_record,
                    const data_violation_type &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_violation_type &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_violation_type& operator=( const data_adapter_violation_type &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_violation_type

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_VIOLATION_TYPE_H__
