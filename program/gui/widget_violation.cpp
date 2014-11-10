/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 10-11-2014
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
#include "combobox_camera_search.h"
#include "combobox_violation_type.h"
#include "combobox_violation_object.h"

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
        this->connect(
                    this->_cbx_cam_name, SIGNAL(currentIndexChanged(int)),
                    this, SLOT(slot_set_camera_address(int))
                     );
        this->connect(
                    this->_cbx_object_name, SIGNAL(violation_type_request(QString)),
                    this, SLOT( slot_refresh_violation_object( QString ) )
                     );
        this->connect(
                    this->_cbx_object_name, SIGNAL(currentIndexChanged(int)),
                    this, SLOT(slot_set_object_id(int))
                     );
        this->connect(
                    this->_btn_save, SIGNAL( clicked( ) ),
                    this, SLOT( save_data_violation( ) )
                     );
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
        this->_cbx_cam_name = new combobox_camera_search;
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
        this->_cbx_violation_type = new combobox_violation_type;
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
        this->_cbx_object_name = new combobox_violation_object;
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
        //_btn_clear
        //
        this->_btn_clear = new QPushButton;
        this->_btn_clear->setIcon(
                          *( new QIcon( ":/image/images/32x32/edit-clear.png") )
                                 );
        this->_btn_clear->setToolTip( QObject::tr( "cancel editing and exit from edit mode" ) );
        hl->addWidget( this->_btn_clear );

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

    /// ------------------------------------------------------------------------
    /// extract_violation( )
    /// ------------------------------------------------------------------------
    data_violation* widget_violation::extract_violation( )
    {
        data_violation *pv = new data_violation( this->_violation );

        pv->violation_type( this->_cbx_violation_type->currentText( ) );
        pv->cam_name( this->_cbx_cam_name->currentText( ) );
        pv->object_type( this->_cbx_object_type->currentText( ) );
        pv->object_name( this->_cbx_object_name->currentText( ) );
        pv->object_id( this->_lbl_id_object->text( ) );
        pv->date_violation( this->_dte_violation->date( ) );
        pv->date_record( QDate::currentDate( ) );
        pv->URL( this->_txt_url->text( ) );
        pv->user( application::program_instance( )->user( ) );

        const data_violation_object *pvo  = this->_cbx_object_name->violation_object( );
        if( pvo )
        {
            pv->okrug( pvo->okrug( ) );
            pv->prefekture( pvo->prefekture( ) );
            pv->district( pvo->district( ) );
        }

        return pv;
    }

    void widget_violation::fill_controls( const data_violation &v )
    {

    }

    bool widget_violation::data_valid( )
    {
        if( !this->camera_valid( ) ) return false;

        if( !this->object_type_valid( ) ) return false;

        if( !this->object_name_valid( ) ) return false;

        if( !this->URL_valid( ) ) return false;

        return true;
    }

    bool widget_violation::camera_valid()
    {
        if( this->_cbx_cam_name->currentIndex( ) < 0 )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "camera\'s name field must be filled" )
                                );
            return false;
        }
        return true;
    }

    bool widget_violation::object_type_valid()
    {
        QString text_obj_type( this->_cbx_object_type->currentText( ).simplified( ).remove( ' ' ) );
        if( !text_obj_type.length( ) )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "object\'s type field must be filled" )
                                );
            return false;
        }
        return true;
    }

    bool widget_violation::object_name_valid()
    {
        if( this->_cbx_object_name->currentIndex( ) < 0 )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "object\'s name field must be filled" )
                                );
            return false;
        }
        return true;
    }

    bool widget_violation::URL_valid( )
    {
        const int MIN_URL_LENGTH = 4;
        if( this->_txt_url->text( ).length( ) < MIN_URL_LENGTH )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "URL field must be filled" )
                                );
            return false;
        }
        return true;
    }

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
    /// ------------------------------------------------------------------------
    /// slot_set_camera_address(int current_cam_index)
    /// ------------------------------------------------------------------------
    void widget_violation::slot_set_camera_address( int current_cam_index )
    {
        if( current_cam_index < 0 )
        {
            this->_lbl_cam_address->setText( "-" );
            return;
        }
        this->_lbl_cam_address->setText(
                    this->_cbx_cam_name->camera_address( current_cam_index )
                    );
    }

    /// ------------------------------------------------------------------------
    /// slot_refresh_violation_object(const QString &text)
    /// ------------------------------------------------------------------------
    void widget_violation::slot_refresh_violation_object(const QString &text)
    {
        QString s_type( this->_cbx_object_type->object_type( ) );
        if( !s_type.length( ) )
        {
            QMessageBox::warning(
                                    0, "warning",
                                    tr( "Violation type must be selected!" )
                                );
        }
        this->_cbx_object_name->refresh( s_type, text );
    }

    /// ------------------------------------------------------------------------
    /// slot_set_object_id( int )
    /// ------------------------------------------------------------------------
    void widget_violation::slot_set_object_id( int current_object_index )
    {
        if( current_object_index < 0 )
        {
            this->_lbl_id_object->setText( "-" );
            return;
        }
        this->_lbl_id_object->setText(

                    QString::number(
                        this->_cbx_object_name->object_id( current_object_index )
                                   )
                    );
    }

    /// ------------------------------------------------------------------------
    /// save_data_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::save_data_violation( )
    {
        if( !this->data_valid( ) )
        {
            return;
        }
        data_violation *pv = this->extract_violation( );

        if( pv )
        {
            application::the_business_logic( ).violation_insert( *pv );
            delete pv;
        }
    }

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
