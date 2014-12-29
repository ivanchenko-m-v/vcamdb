///$Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 29-12-2014
///		Comment		:
/// ============================================================================
#ifndef __DATA_ADAPTER_IMPORT_ODH_H__
#define __DATA_ADAPTER_IMPORT_ODH_H__

#include <QDebug>
#include <QString>
#include <QVector>
#include <QVariant>

#include "qt_sqlite_connection.h"
#include "qt_data_row.h"

namespace vcamdb
{

/// ############################################################################
///			class data_adapter_import_ODH
/// ############################################################################
    class data_adapter_import_ODH
	{
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
        data_adapter_import_ODH( const data_adapter_import_ODH &rhs );

	public:
    /// ------------------------------------------------------------------------
        explicit data_adapter_import_ODH( espira::db::qt_sqlite_connection *pdbms = 0 ) :
			_dbms( pdbms )
		 { }
    /// ------------------------------------------------------------------------
        ~data_adapter_import_ODH( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
	private:
    /// ------------------------------------------------------------------------
		void throw_error( const char* s_msg ) const;
    /// ------------------------------------------------------------------------
        void make_params_insert(espira::db::qt_sqlite_command *pcmd,
                                const QStringList &s_record
                               );
    /// ------------------------------------------------------------------------
        QString trim_quotes( const QString &str );
    /// ------------------------------------------------------------------------
        bool file_exists( const QString &f_name ) const;
    /// ------------------------------------------------------------------------
        void begin_transaction( espira::db::qt_sqlite_connection &cnn );
        void commit_transaction( espira::db::qt_sqlite_connection &cnn );
        void rollback_transaction( espira::db::qt_sqlite_connection &cnn );
    /// ------------------------------------------------------------------------
        void clear_import_table(
                                espira::db::qt_sqlite_connection &cnn,
                                espira::db::qt_sqlite_command *pcmd
                               );
        void insert(espira::db::qt_sqlite_connection &cnn,
                     espira::db::qt_sqlite_command *pcmd,
                     const QStringList &s_record
                   );
        void exec(const QString &cmd_text,
                    espira::db::qt_sqlite_connection &cnn,
                    espira::db::qt_sqlite_command *pcmd
                 );

    public:
    /// ------------------------------------------------------------------------
        void import_file( const QString &f_name );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	private:

	public:

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        data_adapter_import_ODH& operator=( const data_adapter_import_ODH &rhs );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
	private:
		static const QString _s_sql_insert;
        static const QString _s_sql_delete;

        espira::db::qt_sqlite_connection *_dbms;

    };//class data_adapter_import_ODH

/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __DATA_ADAPTER_IMPORT_ODH_H__
