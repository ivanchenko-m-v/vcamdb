/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 02-11-2014
///		Comment		:
/// ============================================================================
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QKeyEvent>
#include <QPrinter>
#include <QPrintPreviewDialog>

#include "application.h"
#include "business_logic.h"

#include "widget_violation.h"

#include "vertical_box.h"

#include "combobox_object_type.h"

namespace ew = espira::widgets;

namespace vcamdb
{
/// ############################################################################
///			class widget_violation
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	widget_violation( )
    /// ------------------------------------------------------------------------
    widget_violation::widget_violation(QWidget *parent) :
        QWidget(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~widget_violation( )
    /// ------------------------------------------------------------------------
    widget_violation::~widget_violation( )
    {

    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    /// ------------------------------------------------------------------------
    /// initialize( )
    /// ------------------------------------------------------------------------
    void widget_violation::initialize( )
    {
        this->init_layout( );

        this->init_connections( );

        //this->_w_search->setFocus( );
    }

    /// ------------------------------------------------------------------------
    /// init_layout( )
    /// ------------------------------------------------------------------------
    void widget_violation::init_layout( )
    {
        QVBoxLayout *layout = new QVBoxLayout;
        layout->setSpacing( 5 );
        layout->setMargin( 0 );

        layout->addStretch( 1000 );
        layout->addWidget( this->init_1st_line( ) );
        layout->addWidget( this->init_2nd_line( ) );
        layout->addWidget( this->init_3rd_line( ) );
        layout->addWidget( this->init_buttons( ) );

        this->setLayout( layout );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_violation::init_connections( )
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
    /// init_1st_line( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_1st_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;

        //
        //_cbx_cam_name
        //
        this->_cbx_cam_name = new QComboBox;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_cam_name,
                                          QObject::tr( "camera name:" ),
                                          this
                                        )
                         );
        //
        //_lbl_cam_address
        //
        this->_lbl_cam_address = new QLabel( "-" );
        layout->addWidget(
                    new ew::vertical_box( this->_lbl_cam_address,
                                          QObject::tr( "camera address:" ),
                                          this
                                        )
                         );
        //
        //_cbx_violation_type
        //
        this->_cbx_violation_type = new QComboBox;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_violation_type,
                                          QObject::tr( "violation type:" ),
                                          this
                                        )
                         );


        QWidget *w = new QWidget( this );
        w->setLayout( layout );

        return w;
    }

    /// ------------------------------------------------------------------------
    /// init_2nd_line( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_2nd_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;

        //
        //_cbx_object_type
        //
        this->_cbx_object_type = new combobox_object_type;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_object_type,
                                          QObject::tr( "object\'s type:" ),
                                          this
                                        )
                         );
        //
        //_cbx_object_name
        //
        this->_cbx_object_name = new QComboBox;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_object_name,
                                          QObject::tr( "object\'s name:" ),
                                          this
                                        )
                         );
        //
        //_lbl_id_object
        //
        this->_lbl_id_object = new QLabel( "-" );
        layout->addWidget(
                    new ew::vertical_box( this->_lbl_id_object,
                                          QObject::tr( "object\'s ID:" ),
                                          this
                                        )
                         );

        QWidget *w = new QWidget( this );
        w->setLayout( layout );

        return w;
    }

    /// ------------------------------------------------------------------------
    /// init_3rd_line( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_3rd_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;

        //
        //_dte_violation
        //
        this->_dte_violation = new QDateEdit;
        this->_dte_violation->setCalendarPopup( true );
        this->_dte_violation->setDate( QDate::currentDate( ) );
        this->_dte_violation->setDisplayFormat( "dd-MM-yyyy" );
        layout->addWidget(
                    new ew::vertical_box( this->_dte_violation,
                                          QObject::tr( "violation\'s date:" ),
                                          this
                                        )
                         );
        //
        //_txt_url
        //
        this->_txt_url = new QLineEdit;
        layout->addWidget(
                    new ew::vertical_box( this->_txt_url,
                                          QObject::tr( "URL to violation\'s facts:" ),
                                          this
                                        )
                         );

        QWidget *w = new QWidget( this );
        w->setLayout( layout );

        return w;
    }

    /// ------------------------------------------------------------------------
    /// init_buttons( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_buttons( )
    {
        QHBoxLayout *hl = new QHBoxLayout;
        hl->setMargin( 5 );
        hl->setSpacing( 5 );

        hl->addStretch( 1000 );

        //
        //_btn_new
        //
        this->_btn_new = new QPushButton;
        this->_btn_new->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-new.png" ) )
                                 );
        this->_btn_new->setToolTip( QObject::tr( "insert new violation\'s data into DB" ) );
        hl->addWidget( this->_btn_new );

        //
        //_btn_edit
        //
        this->_btn_edit = new QPushButton;
        this->_btn_edit->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-edit.png" ) )
                                 );
        this->_btn_edit->setToolTip( QObject::tr( "edit selected violation in the list" ) );
        hl->addWidget( this->_btn_edit );

        //
        //_btn_del
        //
        this->_btn_del = new QPushButton;
        this->_btn_del->setIcon(
                        *( new QIcon( ":/image/images/32x32/document-close.png" ) )
                                 );
        this->_btn_del->setToolTip( QObject::tr( "delete  selected violation in the list from DB" ) );
        hl->addWidget( this->_btn_del );

        //
        //_btn_save
        //
        this->_btn_save = new QPushButton;
        this->_btn_save->setIcon(
                        *( new QIcon( ":/image/images/32x32/media-floppy.png" ) )
                                 );
        this->_btn_save->setToolTip( QObject::tr( "save new or edited violation in the DB" ) );
        hl->addWidget( this->_btn_save );

        QWidget *widget = new QWidget( this );
        widget->setLayout( hl );

        return widget;
    }
/*
    /// ------------------------------------------------------------------------
    /// init_search_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_search_card( )
    {
        this->_w_search = new widget_search_card( this );

        return this->_w_search;
    }

    /// ------------------------------------------------------------------------
    /// init_view_card( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_view_card( )
    {
        this->_w_view = new widget_card_view( this );

        return this->_w_view;
    }

    /// ------------------------------------------------------------------------
    /// init_listview_request( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_listview_request( )
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
    QWidget* widget_violation::init_buttons_search( )
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
    QWidget* widget_violation::init_buttons_listview( )
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
    void widget_violation::init_stat_menu( )
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
    void widget_violation::keyPressEvent( QKeyEvent * event )
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
    void widget_violation::slot_add_request( )
    {
        dialog_request_data w_data_add;
        w_data_add.exec( );
    }

    /// ------------------------------------------------------------------------
    /// slot_edit_request( )
    /// ------------------------------------------------------------------------
    void widget_violation::slot_edit_request( )
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
    void widget_violation::slot_del_request( )
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
    void widget_violation::slot_id_request_edit( )
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
    void widget_violation::slot_print_request( )
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
    void widget_violation::slot_print_preview_paint_requested( QPrinter *p ) const
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
    void widget_violation::slot_stat_report( )
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
    void widget_violation::slot_stat_diagram( )
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
