///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
///		Date update	: 05-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_DT_H__
#define __DATA_ADAPTER_DT_H__

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
///			class data_DT
/// ############################################################################
    class data_DT
	{
    public:
        enum field_data_DT : int
        {
            num_field_dt_id = 0,        //ID_DT INTEGER NOT NULL,
            num_field_okrug = 1,        //OKRUG VARCHAR(256),
            num_field_pref = 2,         //PREF VARCHAR(256),
            num_field_district = 3,     //DISTRICT VARCHAR(256),
            num_field_yard_owner = 4,   //YARD_OWNER_NAME VARCHAR(256),
            num_field_address = 5,      //OBJECT_ADDRESS VARCHAR(512)
            fields_count = 6
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_DT( ) :
            _n_id(0),
            _x_okrug(""),
            _x_prefekt(""),
            _x_district(""),
            _x_yard_owner(""),
            _x_address("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_DT( const data_DT &rhs ) :
            _n_id(rhs._n_id),
            _x_okrug(rhs._x_okrug),
            _x_prefekt(rhs._x_prefekt),
            _x_district(rhs._x_district),
            _x_yard_owner(rhs._x_yard_owner),
            _x_address(rhs._x_address)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_DT( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = row[num_field_dt_id].toInt( );
            this->_x_okrug = row[num_field_okrug].toString( );
            this->_x_prefekt = row[num_field_pref].toString( );
            this->_x_district = row[num_field_district].toString( );
            this->_x_yard_owner = row[num_field_yard_owner].toString( );
            this->_x_address = row[num_field_address].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_DT( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = (*p_row)[num_field_dt_id].toInt( );
            this->_x_okrug = (*p_row)[num_field_okrug].toString( );
            this->_x_prefekt = (*p_row)[num_field_pref].toString( );
            this->_x_district = (*p_row)[num_field_district].toString( );
            this->_x_yard_owner = (*p_row)[num_field_yard_owner].toString( );
            this->_x_address = (*p_row)[num_field_address].toString( );
        }
    /// ------------------------------------------------------------------------
        ~data_DT( )
		{
            qDebug( ) << "deleted : " << this->_n_id << " " +
                                         this->_x_address;
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
            this->_x_prefekt.clear( );
            this->_x_district.clear( );
            this->_x_yard_owner.clear( );
            this->_x_address.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_dt
        int id_dt( ) const
        { return this->_n_id; }

        void id_dt( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	okrug
        const QString& okrug( ) const
        { return this->_x_okrug; }

        void okrug( const QString &x_okrug )
        { this->_x_okrug = x_okrug; }

    /// ------------------------------------------------------------------------
    ///	prefekt
        const QString& prefekt( ) const
        { return this->_x_prefekt; }

        void prefekt( const QString &x_prefekt )
        { this->_x_prefekt = x_prefekt; }

    /// ------------------------------------------------------------------------
    ///	district
        const QString& district( ) const
        { return this->_x_district; }

        void district( const QString &x_district )
        { this->_x_district = x_district; }

    /// ------------------------------------------------------------------------
    ///	yard_owner
        const QString& yard_owner( ) const
        { return this->_x_yard_owner; }

        void yard_owner( const QString &x_yard_owner )
        { this->_x_yard_owner = x_yard_owner; }

    /// ------------------------------------------------------------------------
    ///	address
        const QString& address( ) const
        { return this->_x_address; }

        void address( const QString &x_address )
        { this->_x_address = x_address; }

    /// ------------------------------------------------------------------------
    ///	to_string
        QString to_string( ) const
        {
            return QString::number(this->_n_id) + " | " +
                    this->_x_okrug + " | " + this->_x_address;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_DT& operator=( const data_DT &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_n_id = rhs._n_id;
            this->_x_okrug = rhs._x_okrug;
            this->_x_prefekt = rhs._x_prefekt;
            this->_x_district = rhs._x_district;
            this->_x_yard_owner = rhs._x_yard_owner;
            this->_x_address = rhs._x_address;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _n_id;         //ID_DT INTEGER NOT NULL,
        QString _x_okrug;      //OKRUG VARCHAR(256),
        QString _x_prefekt;    //PREF VARCHAR(256),
        QString _x_district;   //DISTRICT VARCHAR(256),
        QString _x_yard_owner; //YARD_OWNER_NAME VARCHAR(256),
        QString _x_address;    //OBJECT_ADDRESS VARCHAR(512)

    };//class data_DT
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_DT_collection
/// ############################################################################
    class data_DT_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_DT_collection( const data_DT_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_DT_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_DT_collection( )
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
                data_DT *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_DT *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_DT *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_DT *>* list( )
		{ return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_DT *>::iterator iterator;
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
        data_DT_collection& operator=(
                                        const data_DT_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_DT *>	*_data;

    };//class data_DT_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_DT
/// ############################################################################
    class data_adapter_DT
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_DT( const data_adapter_DT &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_DT( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_DT( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_DT &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_DT &old_rec,
                                const data_DT &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_DT &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_DT_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_DT &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_DT &old_record,
                    const data_DT &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_DT &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_DT& operator=( const data_adapter_DT &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_DT

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_DT_H__
