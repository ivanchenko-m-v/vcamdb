///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 10-11-2014
///		Date update	: 13-11-2014
///		Comment		:
/// ============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_violation.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
//ID_VIOLATION INTEGER NOT NULL,
//REGNUM VARCHAR(64),
//VIOLATION_TYPE VARCHAR(256),
//OKRUG VARCHAR(256),
//PREF VARCHAR(256),
//DISTRICT VARCHAR(256),
//CAM_NAME VARCHAR(256),
//OBJECT_TYPE VARCHAR(256),
//OBJECT_ID VARCHAR(256),
//OBJECT_NAME VARCHAR(256),
//VIOLATION_DATE VARCHAR(32),
//RECORD_DATE VARCHAR(32),
//URL VARCHAR(256),
//USER_CREATED VARCHAR(256),
//NOTE VARCHAR(256)

    const QString data_adapter_violation::_s_sql_insert(
                                "INSERT INTO TABLE_VIOLATION "
                                "(ID_VIOLATION, REGNUM, VIOLATION_TYPE, OKRUG, "
                                "PREF, DISTRICT, CAM_NAME, "
                                "OBJECT_TYPE, OBJECT_ID, OBJECT_NAME,"
                                "VIOLATION_DATE, RECORD_DATE, URL,"
                                "USER_CREATED, NOTE) "
                                "   SELECT MAX(ID_VIOLATION)+1, :x_regnum, :x_type, :x_okrug,"
                                          ":x_pref, :x_district, :x_cam_name, "
                                          ":x_obj_type, :x_obj_id, :x_obj_name,"
                                          ":x_dt, :x_dt_rec, :x_url, :x_user, :x_note "
                                    "FROM TABLE_VIOLATION;"
									);
    const QString data_adapter_violation::_s_sql_update(
                                "UPDATE TABLE_VIOLATION"
                                "   SET REGNUM=:x_regnum,"
                                       "VIOLATION_TYPE=:x_type, "
                                       "OKRUG=:x_okrug, "
                                       "PREF=:x_pref, "
                                       "DISTRICT=:x_district, "
                                       "CAM_NAME=:x_cam_name, "
                                       "OBJECT_TYPE=:x_obj_type, "
                                       "OBJECT_ID=:x_obj_id, "
                                       "OBJECT_NAME=:x_obj_name, "
                                       "VIOLATION_DATE=:x_dt, "
                                       "RECORD_DATE=:x_dt_rec, "
                                       "URL=:x_url, "
                                       "USER_CREATED=:x_user, "
                                       "NOTE=:x_note "
                                "WHERE ID_VIOLATION=:x_id_old;"
									);
    const QString data_adapter_violation::_s_sql_delete(
                                "DELETE FROM TABLE_VIOLATION "
                                "WHERE ID_VIOLATION=:x_id;"
									);
    const QString data_adapter_violation::_s_sql_select(
                                "SELECT ID_VIOLATION, REGNUM, VIOLATION_TYPE, OKRUG, "
                                    "PREF, DISTRICT, CAM_NAME, "
                                    "OBJECT_TYPE, OBJECT_ID, OBJECT_NAME,"
                                    "VIOLATION_DATE, RECORD_DATE, URL, "
                                    "USER_CREATED, NOTE "
                                "FROM TABLE_VIOLATION "
									);
/// ############################################################################
///			class data_adapter_violation
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_violation( )
    ///------------------------------------------------------------------------
    data_adapter_violation::~data_adapter_violation( )
	{
	}

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	///------------------------------------------------------------------------
	///	throw_error( const char* s_msg ) const
    ///------------------------------------------------------------------------
    void data_adapter_violation::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_violation::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation &r
                                                   ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.violation_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.reg_number( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.prefekture( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.district( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_id( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_violation( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_record( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.URL( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.user( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.note( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///------------------------------------------------------------------------
    void data_adapter_violation::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation &r
                                                   ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.reg_number( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.violation_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.prefekture( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.district( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_id( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_violation( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_record( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.URL( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.user( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.note( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_violation( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///------------------------------------------------------------------------
    void data_adapter_violation::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_violation( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_violation::make_select_filter( const QString &s_filter ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(USER_CREATED='"+s_filter+"');";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_violation_collection*
        data_adapter_violation::select(const QString &s_filter/*=QString( )*/) const
	{
		//make select query
        QString s_qry( data_adapter_violation::_s_sql_select );
        if( s_filter.length( ) )
        {
            s_qry += this->make_select_filter( s_filter );
        }

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_violation_collection *p_coll = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( s_qry );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );

            //output result
            espira::db::qt_data_row_collection &rows = pcmd->result( );
            if( rows.size( ) )
            {
                p_coll = new data_violation_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    p_coll->append( new data_violation( r ) );
                }
            }

            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            if( p_coll )
            {
                p_coll->free( );
                delete p_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return p_coll;
	}

	///------------------------------------------------------------------------
    ///	insert( const data_violation &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_violation::insert( const data_violation &record ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_violation::_s_sql_insert );
            //add parameters
            this->make_params_insert( pcmd, record );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

	///------------------------------------------------------------------------
    ///	update( const data_violation &ad ) const
	///
    void data_adapter_violation::update( const data_violation &record ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_violation::_s_sql_update );
            //add parameters
            this->make_params_update( pcmd, record );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

	///------------------------------------------------------------------------
    ///	del( const data_violation &ad ) const
	///
    void data_adapter_violation::del( const data_violation &record ) const
	{
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );
            //create command
            pcmd = cnn.create_command( data_adapter_violation::_s_sql_delete );
            //add parameters
            this->make_params_delete( pcmd, record );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //cnn close
            cnn.close( );
            //free memory
            delete pcmd;
        }
        catch( std::exception &ex )
        {
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

/// ############################################################################

}//namespace vcamdb
