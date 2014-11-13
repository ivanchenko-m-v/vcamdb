///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-11-2014
///		Date update	: 13-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_VIOLATION_H__
#define __DATA_ADAPTER_VIOLATION_H__

#include <QDebug>
#include <QString>
#include <QDate>
#include <QTime>
#include <QVector>
#include <QVariant>
#include <QSharedPointer>
#include <QUrl>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_violation
/// ############################################################################
    class data_violation
	{
    public:
        enum field_data_violation : int
        {
            num_field_id = 0,            //ID_VIOLATION INTEGER NOT NULL,
            num_filed_regnum = 1,        //REGNUM VARCHAR(64),
            num_field_type = 2,          //VIOLATION_TYPE VARCHAR(256),
            num_field_okrug = 3,         //OKRUG VARCHAR(256),
            num_field_prefekt = 4,       //PREF VARCHAR(256),
            num_field_district = 5,      //DISTRICT VARCHAR(256),
            num_field_cam_name = 6,      //CAM_NAME VARCHAR(256),
            num_field_object_type = 7,   //OBJECT_TYPE VARCHAR(256),
            num_field_object_id = 8,     //OBJECT_ID VARCHAR(256),
            num_field_object_name = 9,   //OBJECT_NAME VARCHAR(256),
            num_field_date = 10,         //VIOLATION_DATE VARCHAR(32),
            num_field_date_record = 11,  //RECORD_DATE VARCHAR(32),
            num_field_URL = 12,          //URL VARCHAR(256),
            num_field_user = 13,         //USER_CREATED VARCHAR(256),
            num_field_note = 14,         //NOTE VARCHAR(256)
            fields_count = 15
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_violation( ) :
            _n_id(0),
            _x_regnum(""),
            _x_type(""),
            _x_okrug(""),
            _x_prefekt(""),
            _x_district(""),
            _x_cam_name(""),
            _x_object_type(""),
            _x_object_id(""),
            _x_object_name(""),
            _x_date(""),
            _x_date_record(""),
            _x_URL(""),
            _x_user(""),
            _x_note("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation( const data_violation &rhs ) :
            _n_id(rhs._n_id),
            _x_regnum(rhs._x_regnum),
            _x_type(rhs._x_type),
            _x_okrug(rhs._x_okrug),
            _x_prefekt(rhs._x_prefekt),
            _x_district(rhs._x_district),
            _x_cam_name(rhs._x_cam_name),
            _x_object_type(rhs._x_object_type),
            _x_object_id(rhs._x_object_id),
            _x_object_name(rhs._x_object_name),
            _x_date(rhs._x_date),
            _x_date_record(rhs._x_date_record),
            _x_URL(rhs._x_URL),
            _x_user(rhs._x_user),
            _x_note(rhs._x_note)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = row[num_field_id].toInt( );
            this->_x_regnum = row[num_filed_regnum].toString( );
            this->_x_type = row[num_field_type].toString( );
            this->_x_okrug = row[num_field_okrug].toString( );
            this->_x_prefekt = row[num_field_prefekt].toString( );
            this->_x_district = row[num_field_district].toString( );
            this->_x_cam_name = row[num_field_cam_name].toString( );
            this->_x_object_type = row[num_field_object_type].toString( );
            this->_x_object_id = row[num_field_object_id].toString( );
            this->_x_object_name = row[num_field_object_name].toString( );
            this->_x_date = row[num_field_date].toString( );
            this->_x_date_record = row[num_field_date_record].toString( );
            this->_x_URL = row[num_field_URL].toString( );
            this->_x_user = row[num_field_user].toString( );
            this->_x_note = row[num_field_note].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_violation( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_n_id = (*p_row)[num_field_id].toInt( );
            this->_x_regnum = (*p_row)[num_filed_regnum].toString( );
            this->_x_type = (*p_row)[num_field_type].toString( );
            this->_x_okrug = (*p_row)[num_field_okrug].toString( );
            this->_x_prefekt = (*p_row)[num_field_prefekt].toString( );
            this->_x_district = (*p_row)[num_field_district].toString( );
            this->_x_cam_name = (*p_row)[num_field_cam_name].toString( );
            this->_x_object_type = (*p_row)[num_field_object_type].toString( );
            this->_x_object_id = (*p_row)[num_field_object_id].toString( );
            this->_x_object_name = (*p_row)[num_field_object_name].toString( );
            this->_x_date = (*p_row)[num_field_date].toString( );
            this->_x_date_record = (*p_row)[num_field_date_record].toString( );
            this->_x_URL = (*p_row)[num_field_URL].toString( );
            this->_x_user = (*p_row)[num_field_user].toString( );
            this->_x_note = (*p_row)[num_field_note].toString( );
        }
    /// ------------------------------------------------------------------------
        ~data_violation( )
		{
            qDebug( ) << "deleted violation: " << this->to_string( );
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_n_id = 0;
            this->_x_regnum.clear( );
            this->_x_type.clear( );
            this->_x_okrug.clear( );
            this->_x_prefekt.clear( );
            this->_x_district.clear( );
            this->_x_cam_name.clear( );
            this->_x_object_type.clear( );
            this->_x_object_id.clear( );
            this->_x_object_name.clear( );
            this->_x_date.clear( );
            this->_x_date_record.clear( );
            this->_x_URL.clear( );
            this->_x_user.clear( );
            this->_x_note.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_violation
        int id_violation( ) const
        { return this->_n_id; }

        void id_violation( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	reg_number
        const QString& reg_number( ) const
        { return this->_x_regnum; }

        void reg_number( const QString &x_regnum )
        { this->_x_regnum = x_regnum; }

    /// ------------------------------------------------------------------------
    ///	violation_type
        const QString& violation_type( ) const
        { return this->_x_type; }

        void violation_type( const QString &x_type )
        { this->_x_type = x_type; }

    /// ------------------------------------------------------------------------
    ///	okrug
        const QString& okrug( ) const
        { return this->_x_okrug; }

        void okrug( const QString &x_okrug )
        { this->_x_okrug = x_okrug; }

    /// ------------------------------------------------------------------------
    ///	prefekture
        const QString& prefekture( ) const
        { return this->_x_prefekt; }

        void prefekture( const QString &x_prefekt )
        { this->_x_prefekt = x_prefekt; }

    /// ------------------------------------------------------------------------
    ///	district
        const QString& district( ) const
        { return this->_x_district; }

        void district( const QString &x_district )
        { this->_x_district = x_district; }

    /// ------------------------------------------------------------------------
    ///	cam_name
        const QString& cam_name( ) const
        { return this->_x_cam_name; }

        void cam_name( const QString &x_cam_name )
        { this->_x_cam_name = x_cam_name; }

    /// ------------------------------------------------------------------------
    ///	object_type
        const QString& object_type( ) const
        { return this->_x_object_type; }

        void object_type( const QString &x_object_type )
        { this->_x_object_type = x_object_type; }

    /// ------------------------------------------------------------------------
    ///	object_id
        const QString& object_id( ) const
        { return this->_x_object_id; }

        void object_id( const QString &x_object_id )
        { this->_x_object_id = x_object_id; }

    /// ------------------------------------------------------------------------
    ///	object_name
        const QString& object_name( ) const
        { return this->_x_object_name; }

        void object_name( const QString &x_object_name )
        { this->_x_object_name = x_object_name; }

    /// ------------------------------------------------------------------------
    ///	date_violation
        const QString& date_violation( ) const
        { return this->_x_date; }

        QDate dt_violation( ) const
        { return QDate::fromString( this->_x_date, "yyyy-MM-dd" ); }

        void date_violation( const QDate &dt )
        { this->_x_date = dt.toString("yyyy-MM-dd"); }

    /// ------------------------------------------------------------------------
    ///	date_record
        const QString& date_record( ) const
        { return this->_x_date_record; }

        QDate dt_record( ) const
        { return QDate::fromString( this->_x_date_record, "yyyy-MM-dd" ); }

        void date_record( const QDate &dt )
        { this->_x_date_record = dt.toString("yyyy-MM-dd"); }

    /// ------------------------------------------------------------------------
    ///	URL
        const QString& URL( ) const
        { return this->_x_URL; }

        void URL( const QString &x_URL )
        { this->_x_URL = x_URL; }

    /// ------------------------------------------------------------------------
    ///	user
        const QString& user( ) const
        { return this->_x_user; }

        void user( const QString &x_user )
        { this->_x_user = x_user; }

    /// ------------------------------------------------------------------------
    ///	note
        const QString& note( ) const
        { return this->_x_note; }

        void note( const QString &x_note )
        { this->_x_note = x_note; }

    /// ------------------------------------------------------------------------
    ///	to_string
        QString to_string( ) const
        {
            return QString::number( this->_n_id ) + "|" +
                    this->_x_object_type + " | " + this->_x_object_name;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_violation& operator=( const data_violation &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_n_id = rhs._n_id;
            this->_x_regnum = rhs._x_regnum;
            this->_x_type = rhs._x_type;
            this->_x_okrug = rhs._x_okrug;
            this->_x_prefekt = rhs._x_prefekt;
            this->_x_district = rhs._x_district;
            this->_x_cam_name = rhs._x_cam_name;
            this->_x_object_type = rhs._x_object_type;
            this->_x_object_id = rhs._x_object_id;
            this->_x_object_name = rhs._x_object_name;
            this->_x_date = rhs._x_date;
            this->_x_date_record = rhs._x_date_record;
            this->_x_URL = rhs._x_URL;
            this->_x_user = rhs._x_user;
            this->_x_note = rhs._x_note;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int     _n_id;          //ID_VIOLATION INTEGER NOT NULL,
        QString _x_regnum;      //REGNUM VARCHAR(64),
        QString _x_type;        //VIOLATION_TYPE VARCHAR(256),
        QString _x_okrug;       //OKRUG VARCHAR(256),
        QString _x_prefekt;     //PREF VARCHAR(256),
        QString _x_district;    //DISTRICT VARCHAR(256),
        QString _x_cam_name;    //CAM_NAME VARCHAR(256),
        QString _x_object_type; //OBJECT_TYPE VARCHAR(256),
        QString _x_object_id;   //OBJECT_ID VARCHAR(256),
        QString _x_object_name; //OBJECT_NAME VARCHAR(256),
        QString _x_date;        //VIOLATION_DATE VARCHAR(32),
        QString _x_date_record; //RECORD_DATE VARCHAR(32),
        QString _x_URL;         //URL VARCHAR(256),
        QString _x_user;        //USER_CREATED VARCHAR(256),
        QString _x_note;        //NOTE VARCHAR(256)

    };//class data_violation
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_violation_collection
/// ############################################################################
    class data_violation_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_violation_collection( const data_violation_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_violation_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_violation_collection( )
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
                data_violation *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_violation *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_violation *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_violation *>* list( )
		{ return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_violation *>::iterator iterator;
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
        data_violation_collection& operator=(
                                        const data_violation_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_violation *>	*_data;

    };//class data_violation_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_violation
/// ############################################################################
    class data_adapter_violation
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_violation( const data_adapter_violation &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_violation( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_violation( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_violation_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_violation &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_violation &record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_violation &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_violation& operator=( const data_adapter_violation &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_violation

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_VIOLATION_H__
