/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeyEvent>

#include "application.h"
#include "business_logic.h"

#include "widget_cam_selection.h"
#include "vertical_box.h"

namespace ew=espira::widgets;

namespace vcamdb
{
/// ############################################################################
///			class widget_cam_selection
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_cam_selection( )
    /// ------------------------------------------------------------------------
    widget_cam_selection::widget_cam_selection(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_cam_selection( )
    /// ------------------------------------------------------------------------
    widget_cam_selection::~widget_cam_selection( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::initialize( )
    {
        this->init_layout( );

        this->init_connections( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::init_layout( )
    {
        QVBoxLayout *layout = new QVBoxLayout;

        //
        //_txt_address
        //
        this->_txt_address = new QLineEdit;
        layout->addWidget(
                        new ew::vertical_box(
                                            this->_txt_address,
                                            QObject::tr( "object\'s address" ),
                                            this
                                            )
                     );

        //
        //_txt_cam_name
        //
        this->_txt_cam_name = new QLineEdit;
        layout->addWidget(
                        new ew::vertical_box(
                                            this->_txt_cam_name,
                                            QObject::tr( "camera\'s name" ),
                                            this
                                            )
                     );
        //
        //dates period
        //
        layout->addWidget( this->init_period( ) );
        //stretch
        layout->addStretch( 1000 );

        this->setLayout( layout );
    }

    /// ------------------------------------------------------------------------
    /// init_period( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_period( )
    {
        QGridLayout *gl = new QGridLayout;
        gl->setMargin( 0 );
        gl->setSpacing( 0 );

        //
        //_dte_from
        //
        this->_dte_from = new QDateEdit( this );
        this->_dte_from->setCalendarPopup( true );
        this->_dte_from->setDisplayFormat("dd-MM-yyyy");
        this->_dte_from->setDate( QDate::currentDate( ) );
        gl->addWidget(
                        new ew::vertical_box( this->_dte_from,
                                              QObject::tr( "from:" ),
                                              this
                                            ),
                        1, 0
                     );
        //
        //_dte_to
        //
        this->_dte_to = new QDateEdit( this );
        this->_dte_to->setCalendarPopup( true );
        this->_dte_to->setDisplayFormat("dd-MM-yyyy");
        this->_dte_to->setDate( QDate::currentDate( ) );
        gl->addWidget(
                        new ew::vertical_box( this->_dte_to,
                                              QObject::tr( "to:" ),
                                              this
                                            ),
                        1, 2
                     );
        gl->setColumnStretch( 3, 200 );

        QWidget *widget = new QWidget( this );
        widget->setLayout(gl);

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::init_connections( )
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

/*
    /// ------------------------------------------------------------------------
    /// init_search_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_search_card( )
    {
        this->_w_search = new widget_search_card( this );

        return this->_w_search;
    }

    /// ------------------------------------------------------------------------
    /// init_view_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_view_card( )
    {
        this->_w_view = new widget_card_view( this );

        return this->_w_view;
    }

    /// ------------------------------------------------------------------------
    /// init_listview_request( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_listview_request( )
    {
        QWidget *widget = new QWidget( this );

        QVBoxLayout *vl = new QVBoxLayout;
        vl->setMargin( 5 );
        vl->setSpacing( 0 );

        QLabel *lbl = new QLabel( this->tr( "request list:" ), this );

        vl->addWidget( lbl );

        this->_lv_request = new listview_request( this );
        vl->addWidget( this->_lv_request );

       // vl->addStretch( 1000 );

        widget->setLayout( vl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons_search( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_buttons_search( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //_btn_find_request
        this->_btn_find_request = new QPushButton;
        this->_btn_find_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/edit-find.png" ) )
                                 );
        this->_btn_find_request->setToolTip( QObject::tr( "find requests" ) );
        hl->addWidget( this->_btn_find_request );

        //_btn_clear_search_criteria
        this->_btn_clear_search_criteria = new QPushButton;
        this->_btn_clear_search_criteria->setIcon(
                        *( new QIcon( ":/image/images/32x32/edit-clear.png" ) )
                                 );
        this->_btn_clear_search_criteria->setToolTip( QObject::tr( "clear search criteria" ) );
        hl->addWidget( this->_btn_clear_search_criteria );

        //_btn_add_request
        this->_btn_add_request = new QPushButton;
        this->_btn_add_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-new.png" ) )
                                 );
        this->_btn_add_request->setToolTip( QObject::tr( "add declarant\'s request" ) );
        hl->addWidget( this->_btn_add_request );

        widget->setLayout( hl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons_listview( )
    /// ------------------------------------------------------------------------
    QWidget* widget_cam_selection::init_buttons_listview( )
    {
        QWidget *widget = new QWidget( this );

        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //_btn_print_request
        this->_btn_print_request = new QPushButton;
        this->_btn_print_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-print.png" ) )
                                 );
        this->_btn_print_request->setToolTip( QObject::tr( "print request" ) );
        hl->addWidget( this->_btn_print_request );

        //_btn_edit_request
        this->_btn_edit_request = new QPushButton;
        this->_btn_edit_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-edit.png" ) )
                                 );
        this->_btn_edit_request->setToolTip( QObject::tr( "edit request" ) );
        hl->addWidget( this->_btn_edit_request );

        //_btn_edit_id_request
        this->_btn_edit_id_request = new QPushButton;
        this->_btn_edit_id_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/id-request-edit.png" ) )
                                 );
        this->_btn_edit_id_request->setToolTip( QObject::tr( "edit id of the request" ) );
        hl->addWidget( this->_btn_edit_id_request );

        //_btn_del_request
        this->_btn_del_request = new QPushButton;
        this->_btn_del_request->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-close.png" ) )
                                 );
        this->_btn_del_request->setToolTip( QObject::tr( "delete request" ) );
        hl->addWidget( this->_btn_del_request );

        hl->addStretch( 50 );

        //_btn_stat
        this->_btn_stat = new QToolButton;
        this->_btn_stat->setIcon(
                        *( new QIcon( ":/image/images/32x32/office-chart-pie.png" ) )
                                 );
        this->_btn_stat->setToolTip( QObject::tr( "statistics" ) );
        this->_btn_stat->setPopupMode( QToolButton::MenuButtonPopup );
        this->init_stat_menu( );
        this->_btn_stat->setMenu( this->_mnu_stat );
        hl->addWidget( this->_btn_stat );

        widget->setLayout( hl );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// init_stat_menu( )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::init_stat_menu( )
    {
        this->_mnu_stat = new QMenu( );
        this->_act_report = this->_mnu_stat->addAction( tr("Report") );
        this->_act_diagram = this->_mnu_stat->addAction( tr("Diagaram") );
    }
*/

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// keyPressEvent ( QKeyEvent * event )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::keyPressEvent( QKeyEvent * event )
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
    void widget_cam_selection::slot_add_request( )
    {
        dialog_request_data w_data_add;
        w_data_add.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_request( )
    /// ------------------------------------------------------------------------
    void widget_cam_selection::slot_edit_request( )
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
    void widget_cam_selection::slot_del_request( )
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
    void widget_cam_selection::slot_id_request_edit( )
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
    void widget_cam_selection::slot_print_request( )
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
    void widget_cam_selection::slot_print_preview_paint_requested( QPrinter *p ) const
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
    void widget_cam_selection::slot_stat_report( )
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
    void widget_cam_selection::slot_stat_diagram( )
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
