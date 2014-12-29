/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 29-12-2014
///		Comment		:
/// ============================================================================
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFileDialog>

#include "application.h"
#include "business_logic.h"

#include "widget_tab_setup.h"

namespace vcamdb
{
/// ############################################################################
///			class widget_tab_setup
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_tab_setup( )
    /// ------------------------------------------------------------------------
    widget_tab_setup::widget_tab_setup(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_tab_setup( )
    /// ------------------------------------------------------------------------
    widget_tab_setup::~widget_tab_setup( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::init_layout( )
    {
        QVBoxLayout *layout = new QVBoxLayout;

        layout->addWidget( this->init_buttons( ) );
        layout->addStretch( 1000 );

        this->setLayout( layout );
     }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::init_connections( )
    {
        this->connect(
                        this->_btn_import_CA, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_CA( ) )
                     );
        this->connect(
                        this->_btn_import_DT, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_DT( ) )
                     );
        this->connect(
                        this->_btn_import_ODH, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_ODH( ) )
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget* widget_tab_setup::init_buttons( )
    {
        QGridLayout *layout = new QGridLayout;

        //
        //_btn_import_CA
        //
        layout->addWidget( new QLabel("TABLE_CONTAINER_AREA" ), 0, 0 );

        this->_btn_import_CA = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_CA, 0, 1 );

        layout->addWidget( new QWidget, 0, 2 );

        //
        //_btn_import_DT
        //
        layout->addWidget( new QLabel("TABLE_DT" ), 1, 0 );

        this->_btn_import_DT = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_DT, 1, 1 );

        layout->addWidget( new QWidget, 1, 2 );

        //
        //_btn_import_ODH
        //
        layout->addWidget( new QLabel("TABLE_ODH" ), 2, 0 );

        this->_btn_import_ODH = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_ODH, 2, 1 );

        layout->addWidget( new QWidget, 2, 2 );

        layout->setColumnStretch( 2, 1000 );

        QWidget  *widget = new QWidget( this );
        widget->setLayout( layout );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// file_select( const QString &caption )
    /// ------------------------------------------------------------------------
    QString widget_tab_setup::file_select( const QString &caption )
    {
        //если нет - пытаемся выбрать
        QString s_file = QFileDialog::getOpenFileName(
                                           0, caption,
                                           QApplication::applicationDirPath( ),
                                           QString("*.txt;;*.csv")
                                                     );

        if( s_file.isEmpty( ) )
        {
            QMessageBox::warning( 0, tr("warning"), tr( "Data file didn't selected" ) );
        }

        return s_file;
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent ( QKeyEvent * event )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::keyPressEvent( QKeyEvent * event )
    {
        /*
        if( event->key( ) == Qt::Key_N )
        {
            if( event->modifiers( ) & Qt::ControlModifier )
            {
                this->slot_add_request( );
            }
        }
        */
        QWidget::keyPressEvent( event );
    }

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// slot_import_CA( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_CA( )
    {
        QString s_file = this->file_select( "TABLE_CONTAINER_AREA" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        application::the_business_logic( ).CA_import( s_file );
    }

    /// ------------------------------------------------------------------------
    /// slot_import_DT( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_DT( )
    {
        QString s_file = this->file_select( "TABLE_DT" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        application::the_business_logic( ).DT_import( s_file );
    }

    /// ------------------------------------------------------------------------
    /// slot_import_ODH( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_ODH( )
    {
        QString s_file = this->file_select( "TABLE_ODH" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        application::the_business_logic( ).ODH_import( s_file );
    }

}//namespace vcamdb
