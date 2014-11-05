///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-11-2014
///		Date update	: 05-11-2014
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

#include "data_adapter_ODH.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
/// ############################################################################
///			class data_adapter_ODH
/// ############################################################################

    const QString data_adapter_ODH::_s_sql_insert(
                                "INSERT INTO TABLE_ODH "
                                "(ID_ODH, OKRUG, OBJECT_NAME, "
                                "CUSTOMER_NAME, CONTRACTOR_NAME) "
                                "   VALUES(:n_id, :x_okrug, :x_name,"
                                          ":x_customer, :x_contractor);"
                                                );
    const QString data_adapter_ODH::_s_sql_update(
                                "UPDATE TABLE_ODH"
                                "   SET ID_ODH=:n_id_new, "
                                       "OKRUG=:x_okrug, "
                                       "OBJECT_NAME=:x_name, "
                                       "CUSTOMER_NAME=:x_customer, "
                                       "CONTRACTOR_NAME=:x_contractor "
                                "WHERE ID_ODH=:n_id_old;"
									);
    const QString data_adapter_ODH::_s_sql_delete(
                                "DELETE FROM TABLE_ODH "
                                "WHERE ID_ODH=:x_id;"
									);
    const QString data_adapter_ODH::_s_sql_select(
                                "SELECT ID_ODH, OKRUG, OBJECT_NAME, "
                                    "CUSTOMER_NAME, CONTRACTOR_NAME "
                                "FROM TABLE_ODH "
									);
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_ODH( )
    ///------------------------------------------------------------------------
    data_adapter_ODH::~data_adapter_ODH( )
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
    void data_adapter_ODH::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_ODH::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_ODH &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_odh( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.customer( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.contractor( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///------------------------------------------------------------------------
    void data_adapter_ODH::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_ODH &old_rec,
                                            const data_ODH &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.id_odh( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.object_name( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.customer( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.contractor( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( old_rec.id_odh( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///------------------------------------------------------------------------
    void data_adapter_ODH::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_ODH &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_odh( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_ODH::make_select_filter( const QString &s_filter ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(OBJECT_NAME LIKE '"+s_filter+"%')OR";
        s_where += "(OBJECT_NAME LIKE '%"+s_filter+"%')OR";
        s_where += "(OBJECT_NAME LIKE '%"+s_filter+"') ";
        s_where += "ORDER BY OBJECT_NAME;";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_ODH_collection*
        data_adapter_ODH::select(const QString &s_filter/*=QString( )*/) const
	{
		//make select query
        QString s_qry( data_adapter_ODH::_s_sql_select );
        s_qry += this->make_select_filter( s_filter );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_ODH_collection *cam_coll = 0;
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
                cam_coll = new data_ODH_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    cam_coll->append( new data_ODH( r ) );
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
    ///	insert( const data_ODH &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_ODH::insert( const data_ODH &record ) const
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
            pcmd = cnn.create_command( data_adapter_ODH::_s_sql_insert );
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
    ///	update( const data_ODH &ad ) const
	///
    void data_adapter_ODH::update(
                                            const data_ODH &old_record,
                                            const data_ODH &new_record
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
            pcmd = cnn.create_command( data_adapter_ODH::_s_sql_update );
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
    ///	del( const data_ODH &ad ) const
	///
    void data_adapter_ODH::del( const data_ODH &record ) const
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
            pcmd = cnn.create_command( data_adapter_ODH::_s_sql_delete );
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
