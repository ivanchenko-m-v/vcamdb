///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 29-12-2014
///		Comment		:
/// ============================================================================
#include <stdexcept>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <QVector>

#include <QFile>
#include <QTextStream>

#include "application.h"
#include "business_logic.h"

#include "data_adapter_import_ODH.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
/// ############################################################################
///			class data_adapter_import_ODH
/// ############################################################################

const QString data_adapter_import_ODH::_s_sql_insert(
                            "INSERT INTO TABLE_ODH "
                            "(ID_ODH, OKRUG, OBJECT_NAME, "
                            "CUSTOMER_NAME, CONTRACTOR_NAME) "
                            "   VALUES(:n_id, :x_okrug, :x_name,"
                                      ":x_customer, :x_contractor);"
                                            );
    const QString data_adapter_import_ODH::_s_sql_delete(
                                "DELETE FROM TABLE_ODH;"
                                                 );
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_import_ODH( )
    ///------------------------------------------------------------------------
    data_adapter_import_ODH::~data_adapter_import_ODH( )
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
    void data_adapter_import_ODH::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const QStringList &s_record
                                                   )
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( trim_quotes( s_record.at(0) ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( trim_quotes( s_record.at(1) ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( trim_quotes( s_record.at(2) ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( trim_quotes( s_record.at(3) ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( trim_quotes( s_record.at(4) ) ) );
    }

    ///------------------------------------------------------------------------
    ///	trim_quotes
    ///------------------------------------------------------------------------
    QString data_adapter_import_ODH::trim_quotes( const QString &str )
    {
        QString result = str;
        if( result.isEmpty( ) )
        {
            return result;
        }
        if( result[0] == QChar( '\"' ) )
        {
            result.remove( 0, 1 );
        }
        if( result.isEmpty( )||result.isNull() )
        {
            return result;
        }
        if( result[result.length()-1] == QChar( '\"' ) )
        {
            result.remove( result.length()-1, 1 );
        }
        return result;
    }

	///------------------------------------------------------------------------
    ///	insert( const data_CA &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::insert(
                                         espira::db::qt_sqlite_connection &cnn,
                                         espira::db::qt_sqlite_command *pcmd,
                                         const QStringList &s_record
                                       )
    {
            //create command
            pcmd = cnn.create_command( data_adapter_import_ODH::_s_sql_insert );
            //add parameters
            this->make_params_insert( pcmd, s_record );
            //open cmd
            pcmd->open( );
            //exec
            pcmd->execute( );
            //close command
            pcmd->close( );
            //free memory
            delete pcmd;
            pcmd = 0;
    }

    ///------------------------------------------------------------------------
    ///	exec
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::exec(
                                    const QString &cmd_text,
                                    espira::db::qt_sqlite_connection &cnn,
                                    espira::db::qt_sqlite_command *pcmd
                                     )
    {
        pcmd = cnn.create_command( cmd_text );
        //open cmd
        pcmd->open( );
        //exec
        pcmd->execute( );
        //close command
        pcmd->close( );
        //free memory
        delete pcmd;
        pcmd = 0;
    }

    ///------------------------------------------------------------------------
    ///	clear_import_table
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::clear_import_table(
                                    espira::db::qt_sqlite_connection &cnn,
                                    espira::db::qt_sqlite_command *pcmd
                                                   )
    {
        //create command
        this->exec( data_adapter_import_ODH::_s_sql_delete, cnn, pcmd );
    }

    ///------------------------------------------------------------------------
    ///	import_file( const QString &f_name ) const
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::import_file( const QString &f_name )
    {
        QFile file_import( f_name );
        if( !file_import.exists( ) )
        {
            //this->throw_error( f_name + " file not exists\n" );
            return;
        }

        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        try
        {
            const QString &db_path = application::the_business_logic( ).db_path( );
            cnn.db_path( db_path );
            //cnn open
            cnn.open( );

            //start job
            this->begin_transaction( cnn );

            //clear target table
            this->clear_import_table( cnn, pcmd );

            //do import job
            file_import.open( QIODevice::ReadOnly );
            //connect file to stream
            QTextStream stream( &file_import );
            stream.setCodec( "UTF-8" );

            const int FIELDS_COUNT = 5;
            while( !stream.atEnd( ) )
            {
                QString s_line = stream.readLine( );
                QStringList list_fields = s_line.split( "," );

                if( list_fields.count( ) < FIELDS_COUNT )
                {
                    continue;
                }
                this->insert( cnn, pcmd, list_fields );
            }
            file_import.close( );

            //commit job
            this->commit_transaction( cnn );

            //cnn close
            cnn.close( );
        }
        catch( std::exception &ex )
        {
            //cancel job
            this->rollback_transaction( cnn );
            //delete cmd
            if( pcmd )
            {
                pcmd->close( );
                pcmd = 0;
            }
            cnn.close( );

            file_import.close( );

            QString s_err( QString::fromStdString( ex.what( ) ) );
            qDebug( ) << s_err;

            this->throw_error( s_err.toStdString( ).c_str( ) );
        }
    }

    ///------------------------------------------------------------------------
    ///	begin_transaction( const espira::db::qt_sqlite_connection &cnn ) const
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::begin_transaction( espira::db::qt_sqlite_connection &cnn )
    {
        espira::db::qt_sqlite_command *pcmd = 0;
        this->exec( "BEGIN TRANSACTION;", cnn, pcmd );
    }

    ///------------------------------------------------------------------------
    ///	commit_transaction( const espira::db::qt_sqlite_connection &cnn ) const
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::commit_transaction( espira::db::qt_sqlite_connection &cnn )
    {
        espira::db::qt_sqlite_command *pcmd = 0;
        this->exec( "COMMIT TRANSACTION;", cnn, pcmd );
    }

    ///------------------------------------------------------------------------
    ///	rollback_transaction( const espira::db::qt_sqlite_connection &cnn ) const
    ///------------------------------------------------------------------------
    void data_adapter_import_ODH::rollback_transaction( espira::db::qt_sqlite_connection &cnn )
    {
        espira::db::qt_sqlite_command *pcmd = 0;
        this->exec( "ROLLBACK TRANSACTION;", cnn, pcmd );
    }

/// ############################################################################

}//namespace vcamdb
