///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
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

#include "data_adapter_DT.h"
#include "qt_sqlite_command.h"

namespace vcamdb
{
/// ############################################################################
///			class data_adapter_DT
/// ############################################################################

    const QString data_adapter_DT::_s_sql_insert(
                                "INSERT INTO TABLE_DT "
                                "(ID_DT, OKRUG, PREF, "
                                "DISTRICT, YARD_OWNER_NAME, OBJECT_ADDRESS) "
                                "   VALUES(:n_id, :x_okrug, :x_pref,"
                                          ":x_district, :x_yard_owner, :x_address);"
                                                );
    const QString data_adapter_DT::_s_sql_update(
                                "UPDATE TABLE_DT"
                                "   SET ID_DT=:n_id_new, "
                                       "OKRUG=:x_okrug, "
                                       "PREF=:x_pref, "
                                       "DISTRICT=:x_district, "
                                       "YARD_OWNER_NAME=:x_yard_owner, "
                                       "OBJECT_ADDRESS=:x_address "
                                "WHERE ID_DT=:n_id_old;"
									);
    const QString data_adapter_DT::_s_sql_delete(
                                "DELETE FROM TABLE_DT "
                                "WHERE ID_DT=:n_id;"
									);
    const QString data_adapter_DT::_s_sql_select(
                                "SELECT ID_DT, OKRUG, PREF, "
                                    "DISTRICT, YARD_OWNER_NAME, OBJECT_ADDRESS "
                                "FROM TABLE_DT "
									);
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	///------------------------------------------------------------------------
    ///	~data_adapter_DT( )
    ///------------------------------------------------------------------------
    data_adapter_DT::~data_adapter_DT( )
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
    void data_adapter_DT::throw_error( const char* s_msg ) const
	{
		QString sMsg( QObject::tr( s_msg ) );

		throw std::runtime_error( sMsg.toUtf8( ).data( ) );
	}

    ///------------------------------------------------------------------------
    ///	make_params_insert
    ///------------------------------------------------------------------------
    void data_adapter_DT::make_params_insert(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_DT &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_dt( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.prefekt( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.district( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.yard_owner( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( r.address( ) ) );
    }
    ///------------------------------------------------------------------------
    ///	make_params_update
    ///------------------------------------------------------------------------
    void data_adapter_DT::make_params_update(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_DT &old_rec,
                                            const data_DT &new_rec
                           ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( new_rec.id_dt( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.okrug( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.prefekt( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.district( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.yard_owner( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_text( new_rec.address( ) ) );
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( old_rec.id_dt( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_params_delete
    ///------------------------------------------------------------------------
    void data_adapter_DT::make_params_delete(
                                            espira::db::qt_sqlite_command *pcmd,
                                            const data_DT &r
                        ) const
    {
        using namespace espira::db;
        pcmd->parameters( ).append( new qt_sqlite_dbvalue_int( r.id_dt( ) ) );
    }

    ///------------------------------------------------------------------------
    ///	make_select_filter
    ///------------------------------------------------------------------------
    QString data_adapter_DT::make_select_filter( const QString &s_filter ) const
    {
        if( !s_filter.length( ) )
        {
            return QString(";");
        }
        QString s_where(" WHERE ");
        s_where += "(OBJECT_ADDRESS LIKE '"+s_filter+"%')OR";
        s_where += "(OBJECT_ADDRESS LIKE '%"+s_filter+"%')OR";
        s_where += "(OBJECT_ADDRESS LIKE '%"+s_filter+"') ";
        s_where += "ORDER BY OBJECT_ADDRESS;";

        return s_where;
    }

    ///------------------------------------------------------------------------
    ///	select( const QString &s_filter/* = QString( )*/ ) const
    ///------------------------------------------------------------------------
    data_DT_collection*
        data_adapter_DT::select(const QString &s_filter/*=QString( )*/) const
	{
		//make select query
        QString s_qry( data_adapter_DT::_s_sql_select );
        s_qry += this->make_select_filter( s_filter );

        qDebug()<<"preparing: " <<s_qry;

		//run query
        espira::db::qt_sqlite_connection cnn;
        espira::db::qt_sqlite_command *pcmd = 0;
        data_DT_collection *cam_coll = 0;
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
                cam_coll = new data_DT_collection;
                espira::db::qt_data_row_collection::iterator iter = rows.begin( );
                for( ;iter < rows.end(); ++iter )
                {
                    espira::db::qt_data_row *r = *iter;
                    cam_coll->append( new data_DT( r ) );
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
    ///	insert( const data_DT &record ) const
    ///------------------------------------------------------------------------
    void data_adapter_DT::insert( const data_DT &record ) const
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
            pcmd = cnn.create_command( data_adapter_DT::_s_sql_insert );
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
    ///	update( const data_DT &ad ) const
	///
    void data_adapter_DT::update(
                                            const data_DT &old_record,
                                            const data_DT &new_record
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
            pcmd = cnn.create_command( data_adapter_DT::_s_sql_update );
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
    ///	del( const data_DT &ad ) const
	///
    void data_adapter_DT::del( const data_DT &record ) const
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
            pcmd = cnn.create_command( data_adapter_DT::_s_sql_delete );
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
