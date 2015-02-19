///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-02-2015
///		Date update	: 19-02-2015
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

#include "data_adapter_response.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
    const QString data_adapter_response::_s_sql_insert(
                                "INSERT INTO t_response "
                                "(OBJECT_TYPE, x_response) "
                                "   VALUES(:x_type, :x_response);"
									);
    const QString data_adapter_response::_s_sql_update(
                                "UPDATE t_response"
                                "   SET OBJECT_TYPE=:x_type_new, "
                                   "x_response=:x_response_new "
                                "WHERE (OBJECT_TYPE=:x_type_old)AND(x_response=:x_response_old);"
									);
    const QString data_adapter_response::_s_sql_delete(
                                "DELETE FROM t_response "
                                "WHERE (OBJECT_TYPE=:x_type_old)AND(x_response=:x_response_old);"
									);
    const QString data_adapter_response::_s_sql_select(
                                "SELECT OBJECT_TYPE, x_response "
                                "FROM t_response"
									);
/// ############################################################################
///			class data_adapter_response
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_response( )
	///
    data_adapter_response::~data_adapter_response( )
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
    void data_adapter_response::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///
    void data_adapter_response::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_response &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.response( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///
    void data_adapter_response::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_response &old_rec,
                                            const data_response &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.response( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.response( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///
    void data_adapter_response::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_response &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.response( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_response::make_select_filter(
                                                        const QString &s_object_type,
                                                        const QString &s_filter
                                                        ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(((instr(x_response,'" + s_filter + "')>0)OR";
        s_where += "(instr(x_response,'" + s_filter.toUpper( ) + "')>0)OR";
        s_where += "(instr(x_response,'" +
                     s_filter.right(s_filter.length( ) - 1 ).
                                        prepend( s_filter[0].toUpper( ) ) +
                    "')>0)) ";
        s_where += "AND(OBJECT_TYPE='" + s_object_type +"'))";

        s_where += "ORDER BY x_response;";

        return s_where;
    }

    ///------------------------------------------------------------------------
	///	select( ) const
	///
    data_response_collection*
        data_adapter_response::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_response::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_response_collection *ad_coll = 0;
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
                ad_coll = new data_response_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    ad_coll->append( new data_response( r ) );
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
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_response_collection*
                 data_adapter_response::select(
                                                 const QString &s_object_type,
                                                 const QString &s_filter/*=QString( )*/
                                                ) const
    {
        //make select query
        QString s_qry( data_adapter_response::_s_sql_select );
        s_qry += this->make_select_filter( s_object_type, s_filter );

        qDebug()<<"preparing: " <<s_qry;

        //run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_response_collection *p_coll = 0;
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
                p_coll = new data_response_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    p_coll->append( new data_response( r ) );
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
    ///	insert( const data_response &ad ) const
	///
    void data_adapter_response::insert( const data_response &record ) const
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
            pcmd = cnn.create_command( data_adapter_response::_s_sql_insert );
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
    ///	update( const data_response &ad ) const
	///
    void data_adapter_response::update(
                                            const data_response &old_record,
                                            const data_response &new_record
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
            pcmd = cnn.create_command( data_adapter_response::_s_sql_update );
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
    ///	del( const data_response &ad ) const
	///
    void data_adapter_response::del( const data_response &record ) const
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
            pcmd = cnn.create_command( data_adapter_response::_s_sql_delete );
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
