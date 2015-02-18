///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-02-2015
///		Date update	: 18-02-2015
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

#include "data_adapter_contractor.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
    const QString data_adapter_contractor::_s_sql_insert(
                                "INSERT INTO t_contractor "
                                "(OBJECT_TYPE, x_contractor) "
                                "   VALUES(:x_type, :x_contractor);"
									);
    const QString data_adapter_contractor::_s_sql_update(
                                "UPDATE t_contractor"
                                "   SET OBJECT_TYPE=:x_type_new, "
                                   "x_contractor=:x_contractor_new "
                                "WHERE (OBJECT_TYPE=:x_type_old)AND(x_contractor=:x_contractor_old);"
									);
    const QString data_adapter_contractor::_s_sql_delete(
                                "DELETE FROM t_contractor "
                                "WHERE (OBJECT_TYPE=:x_type_old)AND(x_contractor=:x_contractor_old);"
									);
    const QString data_adapter_contractor::_s_sql_select(
                                "SELECT OBJECT_TYPE, x_contractor "
                                "FROM t_contractor"
									);
/// ############################################################################
///			class data_adapter_contractor
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_contractor( )
	///
    data_adapter_contractor::~data_adapter_contractor( )
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
    void data_adapter_contractor::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///
    void data_adapter_contractor::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_contractor &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.contractor( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///
    void data_adapter_contractor::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_contractor &old_rec,
                                            const data_contractor &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.contractor( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.contractor( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///
    void data_adapter_contractor::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_contractor &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.contractor( ) ) );
    }

    ///------------------------------------------------------------------------
	///	select( ) const
	///
    data_contractor_collection*
        data_adapter_contractor::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_contractor::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_contractor_collection *ad_coll = 0;
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
                ad_coll = new data_contractor_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    ad_coll->append( new data_contractor( r ) );
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
    ///	insert( const data_contractor &ad ) const
	///
    void data_adapter_contractor::insert( const data_contractor &record ) const
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
            pcmd = cnn.create_command( data_adapter_contractor::_s_sql_insert );
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
    ///	update( const data_contractor &ad ) const
	///
    void data_adapter_contractor::update(
                                            const data_contractor &old_record,
                                            const data_contractor &new_record
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
            pcmd = cnn.create_command( data_adapter_contractor::_s_sql_update );
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
    ///	del( const data_contractor &ad ) const
	///
    void data_adapter_contractor::del( const data_contractor &record ) const
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
            pcmd = cnn.create_command( data_adapter_contractor::_s_sql_delete );
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
