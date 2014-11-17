///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 03-11-2014
///		Date update	: 17-11-2014
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

#include "data_adapter_camera.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
    const QString data_adapter_camera::_s_sql_insert(
                                "INSERT INTO TABLE_CAM "
                                "(CAM_ID, CAM_NAME, CAM_ADDRESS, "
                                "CAM_TYPE, INSPECTED_FLAG, OVERVIEW_TYPE, "
                                "RELATED_AMOUNT, SELECTION, LAST_MODIFIED,"
                                "USER_LAST_CHANGE) "
                                "   VALUES(:x_id, :x_name, :x_address,"
                                          ":x_type, :x_flag, :x_overview_type, "
                                          ":n_amount, :x_selection,"
                                          ":x_date, :x_user);"
									);
    const QString data_adapter_camera::_s_sql_update(
                                "UPDATE TABLE_CAM"
                                "   SET CAM_ID=:x_id_new, "
                                       "CAM_NAME=:x_name, "
                                       "CAM_ADDRESS=:x_address, "
                                       "CAM_TYPE=:x_type, "
                                       "INSPECTED_FLAG=:x_flag, "
                                       "OVERVIEW_TYPE=:x_overview_type, "
                                       "RELATED_AMOUNT=:n_amount, "
                                       "SELECTION=:x_selection, "
                                       "LAST_MODIFIED=:x_date, "
                                       "USER_LAST_CHANGE=:x_user "
                                "WHERE OBJECT_TYPE=:x_id_old;"
									);
    const QString data_adapter_camera::_s_sql_delete(
                                "DELETE FROM TABLE_CAM "
                                "WHERE CAM_ID=:x_id;"
									);
    const QString data_adapter_camera::_s_sql_select(
                                "SELECT CAM_ID, CAM_NAME, CAM_ADDRESS, "
                                    "CAM_TYPE, INSPECTED_FLAG, OVERVIEW_TYPE, "
                                    "RELATED_AMOUNT, SELECTION, LAST_MODIFIED,"
                                    "USER_LAST_CHANGE "
                                "FROM TABLE_CAM "
									);
/// ############################################################################
///			class data_adapter_camera
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_camera( )
    ///------------------------------------------------------------------------
    data_adapter_camera::~data_adapter_camera( )
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
    void data_adapter_camera::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_camera::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_camera &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_id( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.flag( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.overview_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.related_amount( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.selection( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.date_last_modified( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.user_modified( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///------------------------------------------------------------------------
    void data_adapter_camera::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_camera &old_rec,
                                            const data_camera &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.cam_id( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.cam_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.cam_address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.cam_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.flag( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.overview_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.related_amount( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.selection( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.date_last_modified( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.user_modified( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.cam_id( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///------------------------------------------------------------------------
    void data_adapter_camera::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_camera &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.cam_id( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_camera::make_select_filter( const QString &s_filter ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(CAM_NAME='"+s_filter+"')OR";
        s_where += "(CAM_NAME LIKE '"+s_filter+"%')OR";
        s_where += "(CAM_NAME LIKE '%"+s_filter+"%')OR";
        s_where += "(CAM_NAME LIKE '%"+s_filter+"')OR";
        s_where += "(CAM_ADDRESS LIKE '"+s_filter+"%')OR";
        s_where += "(CAM_ADDRESS LIKE '%"+s_filter+"%')OR";
        s_where += "(CAM_ADDRESS LIKE '%"+s_filter+"') ";
        s_where += "ORDER BY CAM_NAME;";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	make_select_one_filter
    ///------------------------------------------------------------------------
    QString data_adapter_camera::make_select_one_filter( const QString &s_filter ) const
    {
        if( s_filter.isEmpty( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(CAM_NAME='"+s_filter+"');";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_camera_collection*
        data_adapter_camera::select(const QString &s_filter/*=QString( )*/) const
	{
		//make select query
        QString s_qry( data_adapter_camera::_s_sql_select );
        s_qry += this->make_select_filter( s_filter );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_camera_collection *cam_coll = 0;
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
                cam_coll = new data_camera_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    cam_coll->append( new data_camera( r ) );
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
            if( cam_coll )
            {
                cam_coll->free( );
                delete cam_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return cam_coll;
    }

    data_camera* data_adapter_camera::select_one(const QString &s_filter) const
    {
        if( s_filter.isEmpty( ) )
        {
            return 0;
        }
        //make select query
        QString s_qry( data_adapter_camera::_s_sql_select );
        s_qry += this->make_select_one_filter( s_filter );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;

        data_camera *pcam = 0;
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
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                pcam = new data_camera( *iter );
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
            if( pcam )
            {
                delete pcam;
                pcam = 0;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return pcam;
    }

	///------------------------------------------------------------------------
    ///	insert( const data_camera &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_camera::insert( const data_camera &record ) const
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
            pcmd = cnn.create_command( data_adapter_camera::_s_sql_insert );
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
    ///	update( const data_camera &ad ) const
	///
    void data_adapter_camera::update(
                                            const data_camera &old_record,
                                            const data_camera &new_record
                                    ) const
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
            pcmd = cnn.create_command( data_adapter_camera::_s_sql_update );
            //add parameters
            this->make_params_update( pcmd, old_record, new_record );
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
    ///	del( const data_camera &ad ) const
	///
    void data_adapter_camera::del( const data_camera &record ) const
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
            pcmd = cnn.create_command( data_adapter_camera::_s_sql_delete );
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
