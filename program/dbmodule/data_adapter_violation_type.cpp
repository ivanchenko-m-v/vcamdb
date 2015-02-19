///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-10-2014
///		Date update	: 20-02-2015
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

#include "data_adapter_violation_type.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
    const QString data_adapter_violation_type::_s_sql_insert(
                                "INSERT INTO TABLE_VIOLATION_TYPE "
                                "(OBJECT_TYPE, VIOLATION_TYPE, STATUS) "
                                "   VALUES(:x_object_type, :x_violation_type, :n_status);"
									);
    const QString data_adapter_violation_type::_s_sql_update(
                                "UPDATE TABLE_VIOLATION_TYPE"
                                "   SET OBJECT_TYPE=:x_ob_type_new, "
                                    "VIOLATION_TYPE=:x_type_new, "
                                    "STATUS=:n_status_new, "
                                "WHERE ((OBJECT_TYPE=:x_ob_type_old)AND(VIOLATION_TYPE=:x_type_old));"
									);
    const QString data_adapter_violation_type::_s_sql_delete(
                                "DELETE FROM TABLE_VIOLATION_TYPE "
                                "WHERE ((OBJECT_TYPE=:x_ob_type_old)AND(VIOLATION_TYPE=:x_type_old));"
									);
    const QString data_adapter_violation_type::_s_sql_select(
                                "SELECT OBJECT_TYPE, VIOLATION_TYPE, STATUS "
                                "FROM TABLE_VIOLATION_TYPE "
									);
/// ############################################################################
///			class data_adapter_violation_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_violation_type( )
	///
    data_adapter_violation_type::~data_adapter_violation_type( )
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
	///
    void data_adapter_violation_type::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///
    void data_adapter_violation_type::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation_type &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.violation_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.status( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///
    void data_adapter_violation_type::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation_type &old_rec,
                                            const data_violation_type &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.violation_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.status( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.violation_type( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///
    void data_adapter_violation_type::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_violation_type &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.violation_type( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_violation_type::make_select_filter(
                                                        const QString &s_object_type
                                                        ) const
    {
        if( !s_object_type.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "OBJECT_TYPE='" + s_object_type +"'";

        s_where += " ORDER BY VIOLATION_TYPE;";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( ) const
    ///
    data_violation_type_collection*
        data_adapter_violation_type::select( const QString &s_object_type ) const
    {
        //make select query
        QString s_qry( data_adapter_violation_type::_s_sql_select );
        s_qry += this->make_select_filter( s_object_type );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_violation_type_collection *ad_coll = 0;
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
                ad_coll = new data_violation_type_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    ad_coll->append( new data_violation_type( r ) );
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
            if( ad_coll )
            {
                ad_coll->free( );
                delete ad_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return ad_coll;
    }

    ///------------------------------------------------------------------------
	///	select( ) const
	///
    data_violation_type_collection*
        data_adapter_violation_type::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_violation_type::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_violation_type_collection *ad_coll = 0;
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
                ad_coll = new data_violation_type_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    ad_coll->append( new data_violation_type( r ) );
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
            if( ad_coll )
            {
                ad_coll->free( );
                delete ad_coll;
            }
            cnn.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }

        return ad_coll;
	}

	///------------------------------------------------------------------------
    ///	insert( const data_violation_type &ad ) const
	///
    void data_adapter_violation_type::insert( const data_violation_type &record ) const
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
            pcmd = cnn.create_command( data_adapter_violation_type::_s_sql_insert );
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
    ///	update( const data_violation_type &ad ) const
	///
    void data_adapter_violation_type::update(
                                            const data_violation_type &old_record,
                                            const data_violation_type &new_record
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
            pcmd = cnn.create_command( data_adapter_violation_type::_s_sql_update );
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
    ///	del( const data_violation_type &ad ) const
	///
    void data_adapter_violation_type::del( const data_violation_type &record ) const
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
            pcmd = cnn.create_command( data_adapter_violation_type::_s_sql_delete );
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
