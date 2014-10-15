/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#include <QSplitter>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>

#include "application.h"
#include "business_logic.h"

#include "widget_tab_violation.h"

#include "widget_cam_selection.h"
#include "listview_cam_selection.h"
#include "listview_volation.h"
#include "widget_violation.h"

namespace vcamdb
{
/// ############################################################################
///			class widget_tab_violation
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_tab_violation( )
    /// ------------------------------------------------------------------------
    widget_tab_violation::widget_tab_violation(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_tab_violation( )
    /// ------------------------------------------------------------------------
    widget_tab_violation::~widget_tab_violation( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::initialize( )
    {
        this->init_layout( );

        this->init_connections( );

        //this->_w_search->setFocus( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::init_layout( )
    {
        QSplitter *splitter = new QSplitter( this );
        splitter->addWidget( this->init_cam_selection_view( ) );
        splitter->addWidget( this->init_violations_view( ) );
        splitter->setStretchFactor( 0, 50 );
        splitter->setStretchFactor( 1, 5000 );

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget( splitter );

        this->setLayout( layout );
     }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::init_connections( )
    {
        /*
        //_btn_find_request
        this->connect(
                    this->_btn_find_request, SIGNAL( clicked( ) ),
                    this->_w_search, SLOT( find_requests( ) )
                    );
        //_btn_clear_search_criteria
        this->connect(
                    this->_btn_clear_search_criteria, SIGNAL( clicked( ) ),
                    this->_w_search, SLOT( clear_search_criteria( ) )
                    );
        //_btn_add_request
        this->connect(
                    this->_btn_add_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_add_request( ) )
                    );
        //_btn_print_request
        this->connect(
                    this->_btn_print_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_print_request( ) )
                    );
        //_btn_edit_request
        this->connect(
                    this->_btn_edit_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_edit_request( ) )
                    );
        //_btn_edit_id_request
        this->connect(
                    this->_btn_edit_id_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_id_request_edit( ) )
                    );
        //_btn_del_request
        this->connect(
                    this->_btn_del_request, SIGNAL( clicked( ) ),
                    this, SLOT( slot_del_request( ) )
                    );
        //_lv_request
        this->connect(
                     this->_lv_request, SIGNAL(current_request_changed(const data_request*)),
                     this->_w_view, SLOT(change_view(const data_request*))
                     );
        //_act_report
        this->connect(
                     this->_act_report, SIGNAL( triggered( ) ),
                     this, SLOT( slot_stat_report( ) )
                     );
        //_act_diagram
        this->connect(
                     this->_act_diagram, SIGNAL( triggered( ) ),
                     this, SLOT( slot_stat_diagram( ) )
                     );
                     */
    }

    /// ------------------------------------------------------------------------
    /// init_selection_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_tab_violation::init_cam_selection_view( )
    {
        QVBoxLayout *layout = new QVBoxLayout;

        //
        //_w_cam_selection
        //
        this->_w_cam_selection = new widget_cam_selection( this );
        layout->addWidget( this->_w_cam_selection, 200 );
        //
        //_lv_cams
        //
        this->_lv_cams = new listview_cam_selection( this );
        layout->addWidget( this->_lv_cams, 800 );

        QWidget  *widget = new QWidget( this );
        widget->setLayout( layout );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_violations_view( )
    /// ------------------------------------------------------------------------
    QWidget* widget_tab_violation::init_violations_view( )
    {
        QVBoxLayout *layout = new QVBoxLayout;

        //
        //_lv_violations
        //
        this->_lv_violations = new listview_violation( this );
        layout->addWidget( this->_lv_violations, 5000 );
        layout->addStretch( );
        //
        //_w_violation
        //
        this->_w_violation = new widget_violation( this );
        layout->addWidget( this->_w_violation );

        QWidget  *widget = new QWidget( this );
        widget->setLayout( layout );

        return widget;
        /*
        QGridLayout *layout = new QGridLayout;

        //
        //_lv_violations
        //
        this->_lv_violations = new listview_violation( this );
        layout->addWidget( this->_lv_violations, 0, 0 );
         //
        //_w_violation
        //
        this->_w_violation = new widget_violation( this );
        layout->addWidget( this->_w_violation, 2, 0 );

        QWidget  *widget = new QWidget( this );
        widget->setLayout( layout );

        return widget;
        */
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent ( QKeyEvent * event )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::keyPressEvent( QKeyEvent * event )
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
/*
    /// ------------------------------------------------------------------------
    /// slot_add_request( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_add_request( )
    {
        dialog_request_data w_data_add;
        w_data_add.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_request( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_edit_request( )
    {
        data_request *request =
            const_cast<data_request*>( this->_lv_request->current_request( ) );
        if( !request )
        {
            return;
        }
        dialog_request_data w_data_edit( 0, dialog_request_data::mode_edit_request );
        w_data_edit.request( *request );
        int res = w_data_edit.exec( );
        //update data model item
        if( res == QDialog::Accepted )
        {
            *request = w_data_edit.request( );
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_del_request( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_del_request( )
    {
        const data_request *r = this->_lv_request->current_request( );
        if( !r )
        {
            return;
        }
        int i_reply = QMessageBox::question(
                                    0, tr("apply action"),
                                    tr( "Press Yes if you're want delete request" ),
                                    QMessageBox::No|QMessageBox::Yes
                                           );
        if( i_reply == QMessageBox::Yes)
        {
            business_logic &logic = application::the_business_logic( );
            if( logic.request_delete( r->id_request( ) ) )
            {
                QMessageBox::information(
                                         0, tr("info"),
                                         r->id_request_string( ) +
                                         tr(" request successful deleted from db")
                                        );
            }
        }
    }

    /// ------------------------------------------------------------------------
    /// slot_id_request_edit( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_id_request_edit( )
    {
        const data_request *request = this->_lv_request->current_request( );
        if( !request )
        {
            return;
        }
        dialog_id_request dlg;
        dlg.request( const_cast<data_request *>( request ) );
        dlg.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_print_request( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_print_request( )
    {
		const data_request *r = this->_lv_request->current_request( );
		if( !r )
		{
            return;
		}
		QPrinter printer;
		printer.setPageMargins( 15, 15, 15, 15, QPrinter::Millimeter );
		printer.setOrientation( QPrinter::Portrait );
		printer.setPaperSize( QPrinter::A4 );
		printer.setPaperSource( QPrinter::Auto );

		QPrintPreviewDialog ppvw_dlg( &printer );
		ppvw_dlg.setWindowTitle( tr( "Request card info" ) );
		ppvw_dlg.setWindowFlags( Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint );
		this->connect(
				&ppvw_dlg, SIGNAL( paintRequested( QPrinter* ) ),
				this, SLOT( slot_print_preview_paint_requested( QPrinter* ) )
					 );
		ppvw_dlg.exec( );
    }

    /// ------------------------------------------------------------------------
	///	slot_print_preview_paint_requested( QPrinter *p ) const
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_print_preview_paint_requested( QPrinter *p ) const
	{
		//get request
		const data_request *r = this->_lv_request->current_request( );
		if( !r )
		{
            return;
		}
		renderer_request rdr( p );
		rdr.request( r );
		//
		rdr.begin( p );
        rdr.draw_request( );
        rdr.end( );
    }

    /// ------------------------------------------------------------------------
    /// slot_stat_report( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_stat_report( )
    {
        dialog_period dlg;
        if( dlg.exec( ) != QDialog::Accepted )
        {
            return;
        }
        QMessageBox::information(0, "slot_stat_report", "report" );
    }

    /// ------------------------------------------------------------------------
    /// slot_stat_diagram( )
    /// ------------------------------------------------------------------------
    void widget_tab_violation::slot_stat_diagram( )
    {
        dialog_period dlg;
        if( dlg.exec( ) != QDialog::Accepted )
        {
            return;
        }
        QMessageBox::information(0, "slot_stat_diagram", "diagram" );
    }
    */

}//namespace vcamdb
