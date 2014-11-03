///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 03-11-2014
///		Date update	: 03-11-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_CAMERA_H__
#define __DATA_ADAPTER_CAMERA_H__

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
///			class data_camera
/// ############################################################################
    class data_camera
	{
    public:
        enum field_data_camera : int
        {
            num_field_cam_id = 0,          //CAM_ID VARCHAR(256) NOT NULL,
            num_field_cam_name = 1,        //CAM_NAME VARCHAR(256) NOT NULL,
            num_field_address = 2,         //CAM_ADDRESS VARCHAR(256),
            num_field_cam_type = 3,        //CAM_TYPE VARCHAR(256),
            num_field_flag = 4,            //INSPECTED_FLAG VARCHAR(256),
            num_field_overview_type = 5,   //OVERVIEW_TYPE VARCHAR(256),
            num_field_amount = 6,          //RELATED_AMOUNT INTEGER,
            num_field_selection = 7,       //SELECTION VARCHAR(256),
            num_field_last_modified = 8,   //LAST_MODIFIED VARCHAR(16),
            num_field_user_modified = 9,   //USER_LAST_CHANGE VARCHAR(256)
            fields_count = 10
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_camera( ) :
            _x_cam_id(""),
            _x_cam_name(""),
            _x_address(""),
            _x_cam_type(""),
            _x_flag(""),
            _x_overview_type(""),
            _n_amount(0),
            _x_selection(""),
            _x_last_modified(""),
            _x_user_modified("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_camera( const data_camera &rhs ) :
            _x_cam_id(rhs._x_cam_id),
            _x_cam_name(rhs._x_cam_name),
            _x_address(rhs._x_address),
            _x_cam_type(rhs._x_cam_type),
            _x_flag(rhs._x_flag),
            _x_overview_type(rhs._x_overview_type),
            _n_amount(rhs._n_amount),
            _x_selection(rhs._x_selection),
            _x_last_modified(rhs._x_last_modified),
            _x_user_modified(rhs._x_user_modified)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_camera( const QVector<QVariant> &row )
        {
            if( row.size( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_cam_id = row[num_field_cam_id].toString( );
            this->_x_cam_name = row[num_field_cam_name].toString( );
            this->_x_address = row[num_field_address].toString( );
            this->_x_cam_type = row[num_field_cam_type].toString( );
            this->_x_flag = row[num_field_flag].toString( );
            this->_x_overview_type = row[num_field_overview_type].toString( );
            this->_n_amount = row[num_field_amount].toInt( );
            this->_x_selection = row[num_field_selection].toString( );
            this->_x_last_modified = row[num_field_last_modified].toString( );
            this->_x_user_modified = row[num_field_user_modified].toString( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_camera( espira::db::qt_data_row *p_row )
		{
            if( p_row->columns_count( ) < fields_count )
            {
                this->clear_data( );
            }
            this->_x_cam_id = (*p_row)[num_field_cam_id].toString( );
            this->_x_cam_name = (*p_row)[num_field_cam_name].toString( );
            this->_x_address = (*p_row)[num_field_address].toString( );
            this->_x_cam_type = (*p_row)[num_field_cam_type].toString( );
            this->_x_flag = (*p_row)[num_field_flag].toString( );
            this->_x_overview_type = (*p_row)[num_field_overview_type].toString( );
            this->_n_amount = (*p_row)[num_field_amount].toInt( );
            this->_x_selection = (*p_row)[num_field_selection].toString( );
            this->_x_last_modified = (*p_row)[num_field_last_modified].toString( );
            this->_x_user_modified = (*p_row)[num_field_user_modified].toString( );
        }
    /// ------------------------------------------------------------------------
        ~data_camera( )
		{
            qDebug( ) << "deleted : " << this->_x_cam_name << " " +
                                         this->_x_address;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_x_cam_id.clear( );
            this->_x_cam_name.clear( );
            this->_x_address.clear( );
            this->_x_cam_type.clear( );
            this->_x_flag.clear( );
            this->_x_overview_type.clear( );
            this->_n_amount = 0;
            this->_x_selection.clear( );
            this->_x_last_modified.clear( );
            this->_x_user_modified.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	cam_id
        const QString& cam_id( ) const
        { return this->_x_cam_id; }

        void cam_id( const QString &x_cam_id )
        { this->_x_cam_id = x_cam_id; }

    /// ------------------------------------------------------------------------
    ///	cam_name
        const QString& cam_name( ) const
        { return this->_x_cam_name; }

        void cam_name( const QString &x_cam_name )
        { this->_x_cam_name = x_cam_name; }

    /// ------------------------------------------------------------------------
    ///	cam_address
        const QString& cam_address( ) const
        { return this->_x_address; }

        void cam_address( const QString &x_address )
        { this->_x_address = x_address; }

    /// ------------------------------------------------------------------------
    ///	cam_type
        const QString& cam_type( ) const
        { return this->_x_cam_type; }

        void cam_type( const QString &x_cam_type )
        { this->_x_cam_type = x_cam_type; }

    /// ------------------------------------------------------------------------
    ///	flag
        const QString& flag( ) const
        { return this->_x_flag; }

        void flag( const QString &x_flag )
        { this->_x_flag = x_flag; }

    /// ------------------------------------------------------------------------
    ///	overview_type
        const QString& overview_type( ) const
        { return this->_x_overview_type; }

        void overview_type( const QString &x_overview_type )
        { this->_x_overview_type = x_overview_type; }

    /// ------------------------------------------------------------------------
    ///	related_amount
        int related_amount( ) const
        { return this->_n_amount; }

        void related_amount( const int &n_amount )
        { this->_n_amount = n_amount; }

    /// ------------------------------------------------------------------------
    ///	selection
        const QString& selection( ) const
        { return this->_x_selection; }

        void selection( const QString &x_selection )
        { this->_x_selection = x_selection; }

    /// ------------------------------------------------------------------------
    ///	date_last_modified
        const QString& date_last_modified( ) const
        { return this->_x_last_modified; }

        QDate date( ) const
        { return QDate::fromString( this->_x_last_modified, "yyyy-MM-dd" ); }

        void date_last_modified( const QDate &dt )
        { this->_x_last_modified = dt.toString("yyyy-MM-dd"); }

    /// ------------------------------------------------------------------------
    ///	user_modified
        const QString& user_modified( ) const
        { return this->_x_user_modified; }

        void user_modified( const QString &x_user_modified )
        { this->_x_user_modified = x_user_modified; }

    /// ------------------------------------------------------------------------
    ///	to_string
        QString to_string( ) const
        {
            return this->_x_cam_name + " | " + this->_x_address;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_camera& operator=( const data_camera &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_x_cam_id = rhs._x_cam_id;
            this->_x_cam_name = rhs._x_cam_name;
            this->_x_address = rhs._x_address;
            this->_x_cam_type = rhs._x_cam_type;
            this->_x_flag = rhs._x_flag;
            this->_x_overview_type = rhs._x_overview_type;
            this->_n_amount = rhs._n_amount;
            this->_x_selection = rhs._x_selection;
            this->_x_last_modified = rhs._x_last_modified;
            this->_x_user_modified = rhs._x_user_modified;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QString _x_cam_id;          //CAM_ID VARCHAR(256) NOT NULL,
        QString _x_cam_name;        //CAM_NAME VARCHAR(256) NOT NULL,
        QString _x_address;         //CAM_ADDRESS VARCHAR(256),
        QString _x_cam_type;        //CAM_TYPE VARCHAR(256),
        QString _x_flag;            //INSPECTED_FLAG VARCHAR(256),
        QString _x_overview_type;   //OVERVIEW_TYPE VARCHAR(256),
        int     _n_amount;          //RELATED_AMOUNT INTEGER,
        QString _x_selection;       //SELECTION VARCHAR(256),
        QString _x_last_modified;   //LAST_MODIFIED VARCHAR(16),
        QString _x_user_modified;   //USER_LAST_CHANGE VARCHAR(256)

    };//class data_camera
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_camera_collection
/// ############################################################################
    class data_camera_collection
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_camera_collection( const data_camera_collection &rhs );
	public:
    /// ------------------------------------------------------------------------
        data_camera_collection( ) :
			_data( 0 )
		{ }
    /// ------------------------------------------------------------------------
        virtual ~data_camera_collection( )
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
                data_camera *r = this->_data->last( );
				//remove last element from list
				this->_data->removeLast( );
				//delete last element
				delete r;
			}
			delete _data;

			this->_data = 0;
		}

    /// ------------------------------------------------------------------------
        void append( data_camera *r )
		{
			if( !this->_data )
			{
                this->_data = new QList<data_camera *>;
			}
			this->_data->append( r );
		}

    /// ------------------------------------------------------------------------
        QList<data_camera *>* list( )
		{ return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_camera *>::iterator iterator;
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
        data_camera_collection& operator=(
                                        const data_camera_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        QList<data_camera *>	*_data;

    };//class data_camera_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_camera
/// ############################################################################
    class data_adapter_camera
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_camera( const data_adapter_camera &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_camera( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_camera( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_camera &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_camera &old_rec,
                                const data_camera &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_camera &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_camera_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_camera &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_camera &old_record,
                    const data_camera &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_camera &record ) const;

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_camera& operator=( const data_adapter_camera &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_camera

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_CAMERA_H__
