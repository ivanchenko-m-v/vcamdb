///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 29-12-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_VIOLATION_ATTACHMENT_H__
#define __DATA_ADAPTER_VIOLATION_ATTACHMENT_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>
#include <QByteArray>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_violation_attachment
/// ############################################################################
    class data_violation_attachment
	{
    public:
        enum field_data_violation_attachment : int
        {
            num_field_id = 0,           //i_violation_attachment INTEGER UNIQUE PRIMARY KEY,
            num_field_violation_id = 1, //i_violation_id INTEGER,
            num_field_filename = 2,     //x_filename VARCHAR(64),
            num_field_data = 3,         //bin_attachment BLOB
            fields_count = 4
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
        data_violation_attachment( ) :
            _n_id(0),
            _n_violation_id(0),
            _x_filename("")
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_attachment( const data_violation_attachment &rhs ) :
            _n_id(rhs._n_id),
            _n_violation_id(rhs._n_violation_id),
            _x_filename(rhs._x_filename),
            _bin_data(rhs._bin_data)
        { }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_attachment( const QVector<QVariant> &row )
        {
            int n_columns_count = row.size( );
            if( n_columns_count < fields_count )
            {
                this->clear_data( );
                return;
            }
            this->_n_id = row[num_field_id].toInt( );
            this->_n_violation_id = row[num_field_violation_id].toInt( );
            this->_x_filename = row[num_field_filename].toString( );

            if( n_columns_count < num_field_data ) return;
            this->_bin_data = row[num_field_data].toByteArray( );
        }

    /// ------------------------------------------------------------------------
		explicit
        data_violation_attachment( espira::db::qt_data_row *p_row )
        {
            int n_columns_count = p_row->columns_count( );
            if( n_columns_count < fields_count )
            {
                this->clear_data( );
                return;
            }
            this->_n_id = (*p_row)[num_field_id].toInt( );
            this->_n_violation_id = (*p_row)[num_field_violation_id].toInt( );
            this->_x_filename = (*p_row)[num_field_filename].toString( );

            if( n_columns_count < num_field_data ) return;
            this->_bin_data = (*p_row)[num_field_data].toByteArray( );
        }
    /// ------------------------------------------------------------------------
        virtual ~data_violation_attachment( )
		{
            qDebug( ) << "deleted : " << this->_n_id << " " +
                                         this->_x_filename;
		}

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
		void clear_data( )
		{
            this->_n_id = 0;
            this->_n_violation_id = 0;
            this->_x_filename.clear( );
            this->_bin_data.clear( );
        }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
    /// ------------------------------------------------------------------------
    ///	id_dt
        int id_attachment( ) const
        { return this->_n_id; }

        void id_attachment( const int &n_id )
        { this->_n_id = n_id; }

    /// ------------------------------------------------------------------------
    ///	violation_id
        int violation_id( ) const
        { return this->_n_violation_id; }

        void violation_id( const int &n_violation_id )
        { this->_n_violation_id = n_violation_id; }

    /// ------------------------------------------------------------------------
    ///	filename
        const QString& filename( ) const
        { return this->_x_filename; }

        void filename( const QString &x_filename )
        { this->_x_filename = x_filename; }

    /// ------------------------------------------------------------------------
    ///	data
        const QByteArray& data( ) const
        { return this->_bin_data; }

        void data( const QByteArray &x_data )
        { this->_bin_data = x_data; }

    /// ------------------------------------------------------------------------
    ///	to_string
        QString to_string( ) const
        {
            return QString::number(this->_n_id) + " | " +
                    this->_n_violation_id + " | " + this->_x_filename;
        }
    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
	public:
        data_violation_attachment& operator=( const data_violation_attachment &rhs )
		{
			if( this == &rhs )
			{
				return *this;
			}
            this->_n_id = rhs._n_id;
            this->_n_violation_id = rhs._n_violation_id;
            this->_x_filename = rhs._x_filename;
            this->_bin_data = rhs._bin_data;

			return *this;
		}

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
        int        _n_id;          //i_violation_attachment INTEGER UNIQUE PRIMARY KEY,
        int        _n_violation_id;//i_violation_id INTEGER,
        QString    _x_filename;    //x_filename VARCHAR(64),
        QByteArray _bin_data;      //bin_attachment BLOB

    };//class data_violation_attachment
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			data_violation_attachment_collection
/// ############################################################################
    class data_violation_attachment_collection
    {
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    /// ------------------------------------------------------------------------
        data_violation_attachment_collection( const data_violation_attachment_collection &rhs );
    public:
    /// ------------------------------------------------------------------------
        data_violation_attachment_collection( ) :
            _data( 0 )
        { }
    /// ------------------------------------------------------------------------
        virtual ~data_violation_attachment_collection( )
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
                data_violation_attachment *r = this->_data->last( );
                //remove last element from list
                this->_data->removeLast( );
                //delete last element
                delete r;
            }
            delete _data;

            this->_data = 0;
        }

    /// ------------------------------------------------------------------------
        void append( data_violation_attachment *r )
        {
            if( !this->_data )
            {
                this->_data = new QList<data_violation_attachment *>;
            }
            this->_data->append( r );
        }

    /// ------------------------------------------------------------------------
        QList<data_violation_attachment *>* list( )
        { return this->_data; }

    /// ------------------------------------------------------------------------
        typedef QList<data_violation_attachment *>::iterator iterator;
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
        data_violation_attachment_collection& operator=(
                                        const data_violation_attachment_collection &rhs
                                         );
    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QList<data_violation_attachment *>	*_data;

    };//class data_violation_attachment_collection
/// ############################################################################
/// ----------------------------------------------------------------------------

/// ############################################################################
///			class data_adapter_violation_attachment
/// ############################################################################
    class data_adapter_violation_attachment
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_violation_attachment( const data_adapter_violation_attachment &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_violation_attachment( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_violation_attachment( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_attachment &r
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_update(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_attachment &old_rec,
                                const data_violation_attachment &new_rec
                               ) const;
    /// ------------------------------------------------------------------------
        void make_params_delete(
                                espira::db::qt_sqlite_command *pcmd,
                                const data_violation_attachment &r
                               ) const;

    /// ------------------------------------------------------------------------
        QString make_select_filter( const QString &s_filter ) const;

    public:
    /// ------------------------------------------------------------------------
        data_violation_attachment_collection*
                            select( const QString &s_filter = QString( ) ) const;
    /// ------------------------------------------------------------------------
        void insert( const data_violation_attachment &record ) const;
    /// ------------------------------------------------------------------------
        void update(
                    const data_violation_attachment &old_record,
                    const data_violation_attachment &new_record
                   ) const;
    /// ------------------------------------------------------------------------
        void del( const data_violation_attachment &record ) const;

    /// ------------------------------------------------------------------------
        void save_data(
                        const data_violation_attachment &record,
                        const QString &file_path
                      ) const;


    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_violation_attachment& operator=( const data_adapter_violation_attachment &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
		static const QString _s_sql_update;
		static const QString _s_sql_delete;
		static const QString _s_sql_select;

        espira::db::qt_sqlite_connection *_dbms;
    };//class data_adapter_violation_attachment

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_VIOLATION_ATTACHMENT_H__
