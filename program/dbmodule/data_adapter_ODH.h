///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-11-2014
///		Date update	: 09-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_ODH_H__
#define __DATA_ADAPTER_ODH_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

#include "data_violation_object.h"

namespace vcamdb
{

/// ############################################################################
///			class data_ODH
/// ############################################################################
    class data_ODH : data_violation_object
	{
    public:
        enum field_data_ODH : int
        {
            num_field_id = 0,           //ID_ODH INTEGER  NOT NULL,
            num_field_okrug = 1,        //OKRUG VARCHAR(256),
            num_field_object_name = 2,  //OBJECT_NAME VARCHAR(256),
            num_field_customer = 3,     //CUSTOMER_NAME VARCHAR(256),
            num_field_contractor = 4,   //CONTRACTOR_NAME VARCHAR(256)
            fields_count = 5
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_ODH( ) :
            _n_id(0),
            _x_okrug(""),
            _x_object_name(""),
            _x_customer(""),
            _x_contractor("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_ODH( const data_ODH &rhs ) :
            _n_id(rhs._n_id),
            _x_okrug(rhs._x_okrug),
            _x_object_name(rhs._x_object_name),
            _x_customer(rhs._x_customer),
            _x_contractor(rhs._x_contractor)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_ODH( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = row[num_field_id].toInt( );
            this->_x_okrug = row[num_field_okrug].toString( );
            this->_x_object_name = row[num_field_object_name].toString( );
            this->_x_customer = row[num_field_customer].toString( );
            this->_x_contractor = row[num_field_contractor].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_ODH( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = (*p_row)[num_field_id].toInt( );
            this->_x_okrug = (*p_row)[num_field_okrug].toString( );
            this->_x_object_name = (*p_row)[num_field_object_name].toString( );
            this->_x_customer = (*p_row)[num_field_customer].toString( );
            this->_x_contractor = (*p_row)[num_field_contractor].toString( );
        }
    /// ------------------------------------------------------------------------
        virtual ~data_ODH( )
		{
            qDebug( ) << "deleted : " << this->_n_id << " " +
                                         this->_x_object_name;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_n_id = 0;
            this->_x_okrug.clear( );
            this->_x_object_name.clear( );
            this->_x_customer.clear( );
            this->_x_contractor.clear( );
         }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_object( )
        virtual int id_object( ) const
        {
            return this->_n_id;
        }

    /// ------------------------------------------------------------------------
    ///	id_odh
        int id_odh( ) const
        { return this->_n_id; }

        void id_odh( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	okrug
        virtual const QString& okrug( ) const
        { return this->_x_okrug; }

        void okrug( const QString &x_okrug )
        { this->_x_okrug = x_okrug; }

    /// ------------------------------------------------------------------------
    ///	district
        virtual const QString& district( ) const
        {
            return QString( "" );
        }

    /// ------------------------------------------------------------------------
    ///	prefekture
        virtual const QString& prefekture( ) const
        {
            return QString( "" );
        }

    /// ------------------------------------------------------------------------
    ///	object_name
        virtual const QString& object_name( ) const
        { return this->_x_object_name; }

        void object_name( const QString &x_name )
        { this->_x_object_name = x_name; }

    /// ------------------------------------------------------------------------
    ///	customer
        const QString& customer( ) const
        { return this->_x_customer; }

        void customer( const QString &x_customer )
        { this->_x_customer = x_customer; }

    /// ------------------------------------------------------------------------
    ///	contractor
        const QString& contractor( ) const
        { return this->_x_contractor; }

        void contractor( const QString &x_contractor )
        { this->_x_contractor = x_contractor; }

    /// ------------------------------------------------------------------------
    ///	to_string
        QString to_string( ) const
        {
            return QString::number(this->_n_id) + " | " +
                    this->_x_okrug + " | " + this->_x_object_name;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_ODH& operator=( const data_ODH &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_n_id = rhs._n_id;
            this->_x_okrug = rhs._x_okrug;
            this->_x_object_name = rhs._x_object_name;
            this->_x_customer = rhs._x_customer;
            this->_x_contractor = rhs._x_contractor;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _n_id;          //ID_ODH INTEGER  NOT NULL,
        QString _x_okrug;       //OKRUG VARCHAR(256),
        QString _x_object_name; //OBJECT_NAME VARCHAR(256),
        QString _x_customer;    //CUSTOMER_NAME VARCHAR(256),
        QString _x_contractor;  //CONTRACTOR_NAME VARCHAR(256)

    };//class data_ODH
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_ODH_collection
/// ############################################################################
    class data_ODH_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_ODH_collection( const data_ODH_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_ODH_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_ODH_collection( )
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
                data_ODH *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_ODH *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_ODH *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_ODH *>* list( )
		{ return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_ODH *>::iterator iterator;
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
        data_ODH_collection& operator=(
                                        const data_ODH_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_ODH *>	*_data;

    };//class data_ODH_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_ODH
/// ############################################################################
    class data_adapter_ODH
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_ODH( const data_adapter_ODH &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_ODH( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_ODH( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_ODH &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_ODH &old_rec,
                                const data_ODH &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_ODH &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_ODH_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_ODH &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_ODH &old_record,
                    const data_ODH &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_ODH &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_ODH& operator=( const data_adapter_ODH &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_ODH

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_ODH_H__
