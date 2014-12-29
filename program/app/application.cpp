/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 29-12-2014
///		Comment		:
/// ============================================================================
#include <QDebug>
#include <QIcon>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMap>
#include <QTextStream>
#include <QMessageBox>
#include <QTranslator>
#include <stdexcept>

#include "application.h"
#include "business_logic.h"

//namespace ew = espira::widgets;

namespace vcamdb
{
		bool application::_is_logic_initialized = false;
/// ############################################################################
///			class application
/// ############################################################################
	/// ========================================================================
	///		CONSTRUCTORS/DESTRUCTOR
	/// ========================================================================

	/// ------------------------------------------------------------------------
	///	application( int & argc, char ** argv )
    /// ------------------------------------------------------------------------
	application::application( int & argc, char ** argv ) :
        QApplication( argc, argv )
	{
		this->initialize( );
	}


    /// ------------------------------------------------------------------------
	///	~application( )
    /// ------------------------------------------------------------------------
	application::~application( )
	{
		this->closeAllWindows( );

         //close all threads
		if( application::_is_logic_initialized )
		{
			the_business_logic( ).exit( );
		}

        qDebug( ) << "application object destroyed correctly";
    }

	/// ========================================================================
	///		PROPERTIES
	/// ========================================================================

    /// ========================================================================
	///		FUNCTIONS
    /// ========================================================================
	/// -----------------------------------------------------------------------
	///	the_business_logic( )
    /// -----------------------------------------------------------------------
    business_logic& application::the_business_logic( )
	{
		static business_logic logic;

        return logic;
    }
	/// -----------------------------------------------------------------------
	///	the_app_log( )
    /// -----------------------------------------------------------------------
	espira::utils::application_log& application::the_app_log( )
	{
		static espira::utils::application_log app_log;

        return app_log;
	}

    /// ------------------------------------------------------------------------
    ///	authorize( )
    /// ------------------------------------------------------------------------
    void application::authorize( )
    {
        /*
        ew::dialog_authorization dlg;
        if( dlg.exec( ) != QDialog::Accepted )
        {
            return;
        }

        data_mediator* pm = this->the_business_logic( ).
                        mediator_select_authorized( dlg.login( ), dlg.hash( ) );
        if( pm )
        {
            this->_mediator = *pm;
            delete pm;

            //refresh data models with authorized mediator
            the_business_logic( ).mediator_select( );
            the_business_logic( ).ad_select( );
        }
        else
        {
            QMessageBox::critical(
                                    0,
                                    QObject::tr( "error" ),
                                    QObject::tr( "authorization isn't successful" )
                                  );
         }
         */
    }

	/// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
	void application::initialize( )
	{
		try
		{
            this->setWindowIcon(
							*( new QIcon( ":/image/images/app_icon.png" ) )
							   );
            this->load_translation( );
            this->load_config( );
            this->init_db( );
            this->init_logic( );

            this->connect(
                         this, SIGNAL(aboutToQuit( )),
                         this, SLOT(save_config( ))
                         );
		}
		catch( std::exception &ex )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "app init error" ),
									QString::fromUtf8( ex.what( ) )
								  );
		}
		catch( ... )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "critical" ),
									QObject::tr(
												"unexpected error while "
												"program initializing"
												)
								  );
		}
	}

    /// ------------------------------------------------------------------------
	///	init_logic( )
    /// ------------------------------------------------------------------------
    void application::init_logic( )
    {
        if( !application::_is_logic_initialized )
		{
			application::_is_logic_initialized = true;
			//init logic dynamic memory allocated objects
			the_business_logic( ).init( );
		}
    }

    /// ------------------------------------------------------------------------
	///	load_translation( )
    /// ------------------------------------------------------------------------
    void application::load_translation( )
    {
        this->_translator.load(
                        "russian.lng",
                        QApplication::applicationDirPath( )
                       );
        //translation
        this->installTranslator( &( this->_translator ) );
    }

	/// ------------------------------------------------------------------------
	///	load_config( )
    /// ------------------------------------------------------------------------
	void application::load_config( )
	{
        this->_params.parse_cfg_file(
                     QDir::currentPath( )+"/app_vcamdb.cfg"
                    );
    }

    /// ------------------------------------------------------------------------
	///	find_db_file( )
    /// ------------------------------------------------------------------------
    void application::find_db_file( )
    {
        //если файл БД есть - выходим
        if( this->check_db_file( ) )
        {
            return;
        }
        //если нет - пытаемся выбрать
        QString s_file = QFileDialog::getOpenFileName(
                                           0,tr("select db file"),
                                           QApplication::applicationDirPath( ),
                                           QString("*.sqlite;;*.sqlite3")
                                                        );

        if( s_file.length( ) )
        {
            this->_params.parameter("db_path", s_file );
        }
        //проверяем есть ли он после выбора
        if( !this->check_db_file( ) )
        {
            //если его нет - сообщение
            QMessageBox::warning(
                                 0, tr("warning"),
                                 tr("Database file havn\'t been selected")
                                );
        }

    }
    /// ------------------------------------------------------------------------
	///	check_db_file( )
    /// ------------------------------------------------------------------------
    bool application::check_db_file( )
    {
        QString s_db_path = this->_params.parameter("db_path");
        if( s_db_path.length( ) )
        {
            QFile f_db(s_db_path);
            if( f_db.exists( ) )
            {
                return true;
            }
        }
        return false;
    }

    /// ------------------------------------------------------------------------
	///	init_db( )
    /// ------------------------------------------------------------------------
    void application::init_db( )
    {
        this->find_db_file( );
        application::the_business_logic( ).db_path( this->_params.parameter("db_path") );
        application::the_business_logic( ).db_ex_path( this->_params.parameter( "db_attachment" ) );
    }

    /// ========================================================================
	///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
	///	save_config( )
    /// ------------------------------------------------------------------------
    void application::save_config( )
    {
        try
        {
            this->_params.save_cfg_file( QDir::currentPath( )+"/app_vcamdb.cfg" );
        }
        catch( std::exception &ex )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "app exiting error" ),
									QString::fromUtf8( ex.what( ) )
								  );
		}
		catch( ... )
		{
			QMessageBox::critical(
									0,
									QObject::tr( "critical" ),
									QObject::tr(
												"unexpected error while "
												"program exiting"
												)
								  );
        }
    }

/// ############################################################################

}//namespace vcamdb
