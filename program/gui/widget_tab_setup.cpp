/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 19-02-2015
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

#include "listview_violation_type.h"

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

        layout->addWidget( this->init_buttons( ), 1 );
        layout->addWidget( this->init_listview_violation_type( ), 1000 );

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
        this->connect(
                        this->_btn_import_response, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_response( ) )
                     );
        this->connect(
                        this->_btn_import_contractor, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_contractor( ) )
                     );
        this->connect(
                        this->_btn_import_violation_type, SIGNAL( clicked( ) ),
                        this, SLOT( slot_import_violation_type( ) )
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
        layout->addWidget( new QLabel( tr("TABLE_CONTAINER_AREA") ), 0, 0 );
        this->_btn_import_CA = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_CA, 0, 1 );
        layout->addWidget( new QWidget, 0, 2 );

        //
        //_btn_import_DT
        //
        layout->addWidget( new QLabel( tr("TABLE_DT") ), 1, 0 );
        this->_btn_import_DT = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_DT, 1, 1 );
        layout->addWidget( new QWidget, 1, 2 );

        //
        //_btn_import_ODH
        //
        layout->addWidget( new QLabel(tr("TABLE_ODH") ), 2, 0 );
        this->_btn_import_ODH = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_ODH, 2, 1 );
        layout->addWidget( new QWidget, 2, 2 );

        //
        //_btn_import_response
        //
        layout->addWidget( new QLabel( tr("table_response") ), 0, 3 );
        this->_btn_import_response = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_response, 0, 4 );
        layout->addWidget( new QWidget, 0, 5 );

        //
        //_btn_import_contractor
        //
        layout->addWidget( new QLabel( tr("table_contractor") ), 1, 3 );
        this->_btn_import_contractor = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_contractor, 1, 4 );
        layout->addWidget( new QWidget, 1, 5 );

        //
        //_btn_import_violation_type
        //
        layout->addWidget( new QLabel( tr("table_violation_type") ), 2, 3 );
        this->_btn_import_violation_type = new QPushButton( tr( "Import..." ) );
        layout->addWidget( this->_btn_import_violation_type, 2, 4 );
        layout->addWidget( new QWidget, 2, 5 );

        layout->setColumnStretch( 5, 1000 );

        QWidget  *widget = new QWidget( this );
        widget->setLayout( layout );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_listview_violation_type( )
    /// ------------------------------------------------------------------------
    QWidget* widget_tab_setup::init_listview_violation_type( )
    {
        QGridLayout *layout = new QGridLayout;

        //
        //_lv_violation_type
        //
        layout->addWidget( new QLabel( tr( "violation types:" ) ), 0, 0, 1, 2 );

        this->_lv_violation_type = new listview_violation_type;
        layout->addWidget( this->_lv_violation_type, 1, 0, 1, 2 );

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

    /// ------------------------------------------------------------------------
    /// slot_import_response( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_response( )
    {
        QString s_file = this->file_select( "t_response" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        application::the_business_logic( ).response_import( s_file );
    }

    /// ------------------------------------------------------------------------
    /// slot_import_contractor( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_contractor( )
    {
        QString s_file = this->file_select( "t_contractor" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        application::the_business_logic( ).contractor_import( s_file );
    }

    /// ------------------------------------------------------------------------
    /// slot_import_violation_type( )
    /// ------------------------------------------------------------------------
    void widget_tab_setup::slot_import_violation_type( )
    {
        QString s_file = this->file_select( "t_violation_type" );

        if( s_file.isEmpty( ) )
        {
            return;
        }
        //application::the_business_logic( ).contractor_import( s_file );
    }

}//namespace vcamdb
