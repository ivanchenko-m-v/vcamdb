///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 31-10-2014
///		Date update	: 02-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_OBJECT_TYPE_H__
#define __DATA_ADAPTER_OBJECT_TYPE_H__

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
///			class data_object_type
/// ############################################################################
    class data_object_type
	{
    public:
        enum field_data_object_type : int
        {
            num_field_type = 0,
            num_field_description = 1,
            fields_count = 2
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_object_type( ) :
            _x_type(""),
            _x_description("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_object_type( const data_object_type &rhs ) :
            _x_type(rhs._x_type),
            _x_description(rhs._x_description)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_object_type( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_type = row[num_field_type].toString( );
            this->_x_description = row[num_field_description].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_object_type( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_type = (*p_row)[num_field_type].toString( );
            this->_x_description = (*p_row)[num_field_description].toString( );
		}
    /// ------------------------------------------------------------------------
        ~data_object_type( )
		{
            qDebug( ) << "deleted : " << this->_x_type << " " +
                                         this->_x_description;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_x_type.clear();
            this->_x_description.clear();
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	object_type
        const QString& object_type( ) const
        { return this->_x_type; }

        void object_type( const QString &x_ad )
        { this->_x_type = x_ad; }

    /// ------------------------------------------------------------------------
    ///	description
        const QString& description( ) const
        { return this->_x_description; }

        void description( const QString &x_ad_abbreviation )
        { this->_x_description = x_ad_abbreviation; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_object_type& operator=( const data_object_type &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_x_type = rhs._x_type;
            this->_x_description = rhs._x_description;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QString _x_type;       //--тип объекта видеонаблюдения
        QString _x_description;//--описание объекта видеонаблюдения

    };//class data_object_type
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_object_type_collection
/// ############################################################################
    class data_object_type_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_object_type_collection( const data_object_type_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_object_type_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_object_type_collection( )
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
                data_object_type *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_object_type *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_object_type *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_object_type *>* list( )
		{ return this->_data; }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	private:
        data_object_type_collection& operator=(
                                        const data_object_type_collection &rhs
											);
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_object_type *>	*_data;

    };//class data_object_type_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_object_type
/// ############################################################################
    class data_adapter_object_type
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_object_type( const data_adapter_object_type &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_object_type( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_object_type( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_object_type &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_object_type &old_rec,
                                const data_object_type &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_object_type &r
                               ) const;

    public:
    /// ------------------------------------------------------------------------
        data_object_type_collection* select( ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_object_type &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_object_type &old_record,
                    const data_object_type &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_object_type &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_object_type& operator=( const data_adapter_object_type &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_object_type

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_OBJECT_TYPE_H__
