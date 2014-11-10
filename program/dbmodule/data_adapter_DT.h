///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
///		Date update	: 09-11-2014
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

#include "data_violation_object.h"

namespace vcamdb
{

/// ############################################################################
///			class data_DT
/// ############################################################################
    class data_DT : public data_violation_object
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
        virtual ~data_DT( )
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
    ///	id_object( )
        virtual int id_object( ) const
        {
            return this->_n_id;
        }

    /// ------------------------------------------------------------------------
    ///	id_dt
        int id_dt( ) const
        { return this->_n_id; }

        void id_dt( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	okrug
        virtual const QString& okrug( ) const
        { return this->_x_okrug; }

        void okrug( const QString &x_okrug )
        { this->_x_okrug = x_okrug; }

    /// ------------------------------------------------------------------------
    ///	prefekture
        virtual const QString& prefekture( ) const
        { return this->_x_prefekt; }

        void prefekture( const QString &x_prefekt )
        { this->_x_prefekt = x_prefekt; }

    /// ------------------------------------------------------------------------
    ///	district
        virtual const QString& district( ) const
        { return this->_x_district; }

        void district( const QString &x_district )
        { this->_x_district = x_district; }

    /// ------------------------------------------------------------------------
    ///	object_name
        virtual const QString& object_name( ) const
        {
            return this->_x_address;
        }

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
        data_violation_object_collection*
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
