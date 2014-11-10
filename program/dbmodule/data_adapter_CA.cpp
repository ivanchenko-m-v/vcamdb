///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-11-2014
///		Date update	: 10-11-2014
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

#include "data_adapter_CA.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
/// ############################################################################
///			class data_adapter_CA
/// ############################################################################

    const QString data_adapter_CA::_s_sql_insert(
                                "INSERT INTO TABLE_CONTAINER_AREA "
                                "(ID_CONTAINER_AREA, YARD_ID, OBJECT_ADDRESS, "
                                "OKRUG, DISTRICT_NAME) "
                                "   VALUES(:n_id, :n_yard_id, :x_address, "
                                          ":x_okrug, :x_district);"
                                                );
    const QString data_adapter_CA::_s_sql_update(
                                "UPDATE TABLE_CONTAINER_AREA"
                                "   SET ID_CONTAINER_AREA=:n_id_new, "
                                       "YARD_ID=:n_yard_id, "
                                       "OBJECT_ADDRESS=:x_address, "
                                       "OKRUG=:x_okrug, "
                                       "DISTRICT_NAME=:x_district "
                                "WHERE ID_CONTAINER_AREA=:x_id_old;"
									);
    const QString data_adapter_CA::_s_sql_delete(
                                "DELETE FROM TABLE_CONTAINER_AREA "
                                "WHERE ID_CONTAINER_AREA=:n_id;"
									);
    const QString data_adapter_CA::_s_sql_select(
                                "SELECT ID_CONTAINER_AREA, YARD_ID, OBJECT_ADDRESS, "
                                    "OKRUG, DISTRICT_NAME "
                                "FROM TABLE_CONTAINER_AREA "
									);
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_CA( )
    ///------------------------------------------------------------------------
    data_adapter_CA::~data_adapter_CA( )
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
    void data_adapter_CA::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_CA::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_CA &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_ca( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_yard( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.district( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///------------------------------------------------------------------------
    void data_adapter_CA::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_CA &old_rec,
                                            const data_CA &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.id_ca( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.id_yard( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.district( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( old_rec.id_ca( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///------------------------------------------------------------------------
    void data_adapter_CA::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_CA &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_ca( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_CA::make_select_filter( const QString &s_filter ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "((instr(OBJECT_ADDRESS,'" + s_filter + "')>0)OR";
        s_where += "(instr(OBJECT_ADDRESS,'" + s_filter.toUpper( ) + "')>0)OR";
        s_where += "(instr(OBJECT_ADDRESS,'" +
                     s_filter.right(s_filter.length( ) - 1 ).
                                        prepend( s_filter[0].toUpper( ) ) +
                    "')>0)) ";

        s_where += "ORDER BY OBJECT_ADDRESS;";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_violation_object_collection*
                    data_adapter_CA::select(const QString &s_filter/*=QString( )*/) const
	{
		//make select query
        QString s_qry( data_adapter_CA::_s_sql_select );
        s_qry += this->make_select_filter( s_filter );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_violation_object_collection *cam_coll = 0;
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
                cam_coll = new data_violation_object_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    cam_coll->append( new data_CA( r ) );
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

	///------------------------------------------------------------------------
    ///	insert( const data_CA &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_CA::insert( const data_CA &record ) const
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
            pcmd = cnn.create_command( data_adapter_CA::_s_sql_insert );
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
    ///	update( const data_CA &ad ) const
	///
    void data_adapter_CA::update(
                                            const data_CA &old_record,
                                            const data_CA &new_record
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
            pcmd = cnn.create_command( data_adapter_CA::_s_sql_update );
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
    ///	del( const data_CA &ad ) const
	///
    void data_adapter_CA::del( const data_CA &record ) const
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
            pcmd = cnn.create_command( data_adapter_CA::_s_sql_delete );
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
