/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 23-04-2014
///		Date update	: 24-04-2014
///		Comment		:
/// ============================================================================
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

#include "application_log.h"

namespace espira
{

namespace utils
{
/// ############################################################################
///			class application_log
/// ############################################################################

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// write_log( const QString &f_path )
    /// ------------------------------------------------------------------------
    void application_log::write_log(
                                    const QString &f_path,
                                    const QString &s_category,
                                    const QString &s_msg
                                   )
    {
        if( f_path.length( ) )
        {
            this->_f_path = f_path;
        }
        try
        {
            QFile fcfg( this->_f_path );
            fcfg.open( QIODevice::Append|QIODevice::WriteOnly );
            //connect file to stream
            QTextStream stream( &fcfg );
            stream.setCodec( "UTF-8" );
            qDebug( ) << "writing log file...\n";
            stream << QDateTime::currentDateTime( ).toString( Qt::SystemLocaleLongDate )
                   << "\t" << s_category<< "\t" << s_msg << "\r\n";
            stream.flush( );
            fcfg.close( );
        }
        catch( std::exception &ex )
        {
            qDebug( ) << "application_log::write_log "
                      << QString::fromStdString( ex.what( ) );
        }
        catch( ... )
        {
            qDebug( ) << "application_log::write_log unknown error";
        }
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///
    /// ------------------------------------------------------------------------

}//namespace utils

}//namespace espira
