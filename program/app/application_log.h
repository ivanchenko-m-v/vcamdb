/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 23-04-2014
///		Date update	: 23-04-2014
///		Comment		:
/// ============================================================================
#ifndef __APPLICATION_LOG_H__
#define __APPLICATION_LOG_H__

#include <QObject>
#include <QHash>

namespace espira
{

namespace utils
{
/// ############################################################################
///			class application_log
/// ############################################################################
    class application_log : public QObject
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        application_log( const application_log &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit application_log(
                                const QString &f_path=QString( ),
                                QObject *parent=0
                                ) :
                                QObject( parent ),
                                _f_path( f_path )
        { }
        /// --------------------------------------------------------------------
        virtual ~application_log( )
        { }

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        /// log_file_path
        const QString& log_file_path( ) const
        { return this->_f_path; }

        void log_file_path( const QString &f_path )
        { this->_f_path = f_path; }


    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------

    public:
        /// --------------------------------------------------------------------
        void write_log(
                        const QString &f_path=QString( ),
                        const QString &s_category=QString( ),
                        const QString &s_msg=QString( )
                      );

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        application_log& operator=( const application_log &rhs );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    public slots:
        /// --------------------------------------------------------------------

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QString _f_path;

	};//class ini_file_parser
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace utils

}//namespace espira
#endif // __APPLICATION_LOG_H__
