///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 31-10-2014
///		Date update	: 02-11-2014
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

#include "data_adapter_object_type.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
    const QString data_adapter_object_type::_s_sql_insert(
                                "INSERT INTO TABLE_OBJECT_TYPES "
                                "(OBJECT_TYPE, OBJECT_TYPE_DESCRIPTION) "
                                "   VALUES(:x_type, :x_description);"
									);
    const QString data_adapter_object_type::_s_sql_update(
                                "UPDATE TABLE_OBJECT_TYPES"
                                "   SET OBJECT_TYPE=:x_type_new, "
                                   "OBJECT_TYPE_DESCRIPTION=:x_new_description "
                                "WHERE OBJECT_TYPE=:x_type_old;"
									);
    const QString data_adapter_object_type::_s_sql_delete(
                                "DELETE FROM TABLE_OBJECT_TYPES "
                                "WHERE OBJECT_TYPE=:x_type;"
									);
    const QString data_adapter_object_type::_s_sql_select(
                                "SELECT OBJECT_TYPE, OBJECT_TYPE_DESCRIPTION "
                                "FROM TABLE_OBJECT_TYPES"
									);
/// ############################################################################
///			class data_adapter_object_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_object_type( )
	///
    data_adapter_object_type::~data_adapter_object_type( )
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
    void data_adapter_object_type::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///
    void data_adapter_object_type::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_object_type &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.description( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///
    void data_adapter_object_type::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_object_type &old_rec,
                                            const data_object_type &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.object_type( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.description( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( old_rec.object_type( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///
    void data_adapter_object_type::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_object_type &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.object_type( ) ) );
    }

    ///------------------------------------------------------------------------
	///	select( ) const
	///
    data_object_type_collection*
        data_adapter_object_type::select( ) const
	{
		//make select query
        QString s_qry( data_adapter_object_type::_s_sql_select );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_object_type_collection *ad_coll = 0;
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
                ad_coll = new data_object_type_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    ad_coll->append( new data_object_type( r ) );
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
    ///	insert( const data_object_type &ad ) const
	///
    void data_adapter_object_type::insert( const data_object_type &record ) const
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
            pcmd = cnn.create_command( data_adapter_object_type::_s_sql_insert );
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
    ///	update( const data_object_type &ad ) const
	///
    void data_adapter_object_type::update(
                                            const data_object_type &old_record,
                                            const data_object_type &new_record
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
            pcmd = cnn.create_command( data_adapter_object_type::_s_sql_update );
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
    ///	del( const data_object_type &ad ) const
	///
    void data_adapter_object_type::del( const data_object_type &record ) const
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
            pcmd = cnn.create_command( data_adapter_object_type::_s_sql_delete );
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
