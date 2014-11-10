///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-11-2014
///		Date update	: 10-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_CA_H__
#define __DATA_ADAPTER_CA_H__

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
///			class data_CA
/// ############################################################################
    class data_CA : public data_violation_object
	{
    public:
        enum field_data_CA : int
        {
            num_field_dt_id = 0,     //ID_CONTAINER_AREA INTEGER  NOT NULL,
            num_field_id_yard = 1,   //YARD_ID INTEGER,
            num_field_address = 2,   //OBJECT_ADDRESS VARCHAR(512),
            num_field_okrug = 3,     //OKRUG VARCHAR(256),
            num_field_district = 4,  //DISTRICT_NAME  VARCHAR(256)
            fields_count = 5
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_CA( ) :
            _n_id(0),
            _n_yard_id(0),
            _x_address(""),
            _x_okrug(""),
            _x_district("")
         { }

    /// ------------------------------------------------------------------------
		explicit
        data_CA( const data_CA &rhs ) :
            _n_id(rhs._n_id),
            _n_yard_id(rhs._n_yard_id),
            _x_address(rhs._x_address),
            _x_okrug(rhs._x_okrug),
            _x_district(rhs._x_district)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_CA( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = row[num_field_dt_id].toInt( );
            this->_n_yard_id = row[num_field_id_yard].toInt( );
            this->_x_address = row[num_field_address].toString( );
            this->_x_okrug = row[num_field_okrug].toString( );
            this->_x_district = row[num_field_district].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_CA( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = (*p_row)[num_field_dt_id].toInt( );
            this->_n_yard_id = (*p_row)[num_field_id_yard].toInt( );
            this->_x_address = (*p_row)[num_field_address].toString( );
            this->_x_okrug = (*p_row)[num_field_okrug].toString( );
            this->_x_district = (*p_row)[num_field_district].toString( );
        }
    /// ------------------------------------------------------------------------
        virtual ~data_CA( )
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
            this->_n_yard_id = 0;
            this->_x_okrug.clear( );
            this->_x_district.clear( );
            this->_x_address.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_ca
        int id_ca( ) const
        { return this->_n_id; }

        void id_ca( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	id_object( )
        virtual int id_object( ) const
        {
            return this->_n_id;
        }

    /// ------------------------------------------------------------------------
    ///	okrug
        virtual const QString& okrug( ) const
        { return this->_x_okrug; }

        void okrug( const QString &x_okrug )
        { this->_x_okrug = x_okrug; }

    /// ------------------------------------------------------------------------
    ///	district
        virtual const QString& district( ) const
        { return this->_x_district; }

        void district( const QString &x_district )
        { this->_x_district = x_district; }

    /// ------------------------------------------------------------------------
    ///	prefekture
        virtual const QString& prefekture( ) const
        {
            return this->_x_pref;
        }

    /// ------------------------------------------------------------------------
    ///	object_name
        virtual const QString& object_name( ) const
        {
            return this->_x_address;
        }

    /// ------------------------------------------------------------------------
    ///	id_yard
        int id_yard( ) const
        { return this->_n_yard_id; }

        void id_yard( const int &n_yard_id )
        { this->_n_yard_id = n_yard_id; }

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
        data_CA& operator=( const data_CA &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_n_id = rhs._n_id;
            this->_n_yard_id = rhs._n_yard_id;
            this->_x_address = rhs._x_address;
            this->_x_okrug = rhs._x_okrug;
            this->_x_district = rhs._x_district;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _n_id;         //ID_CONTAINER_AREA INTEGER  NOT NULL,
        int     _n_yard_id;    //YARD_ID INTEGER,
        QString _x_address;    //OBJECT_ADDRESS VARCHAR(512),
        QString _x_okrug;      //OKRUG VARCHAR(256),
        QString _x_district;   //DISTRICT_NAME  VARCHAR(256)

        QString _x_pref;

    };//class data_CA
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_CA
/// ############################################################################
    class data_adapter_CA
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_CA( const data_adapter_CA &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_CA( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_CA( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_CA &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_CA &old_rec,
                                const data_CA &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_CA &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_violation_object_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_CA &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_CA &old_record,
                    const data_CA &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_CA &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_CA& operator=( const data_adapter_CA &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_CA

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_CA_H__
