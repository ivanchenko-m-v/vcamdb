/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 19-11-2014
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

        this->controls_disable( );

        this->_cbx_cam_name->setFocus( );
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
        layout->addWidget( this->init_0_line( ) );
        layout->addWidget( this->init_1st_line( ) );
        layout->addWidget( this->init_2nd_line( ) );
        layout->addWidget( this->init_3rd_line( ) );
        layout->addWidget( this->init_4th_line( ) );
        layout->addWidget( this->init_buttons( ) );

        this->setLayout( layout );
    }

    /// ------------------------------------------------------------------------
    /// init_connections( )
    /// ------------------------------------------------------------------------
    void widget_violation::init_connections( )
    {
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
        this->connect(
                    this->_btn_new, SIGNAL( clicked( ) ),
                    this, SLOT( new_data_violation( ) )
                     );
        this->connect(
                    this->_btn_clear, SIGNAL( clicked( ) ),
                    this, SLOT( clear_data_violation( ) )
                     );
        this->connect(
                    this->_btn_edit, SIGNAL( clicked( ) ),
                    this, SLOT( edit_data_violation( ) )
                     );
        this->connect(
                    this->_btn_del, SIGNAL( clicked( ) ),
                    this, SLOT( delete_data_violation( ) )
                     );
    }

    /// ------------------------------------------------------------------------
    /// init_0_line( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_0_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;
        //
        //_lbl_user
        //
        this->_lbl_user = new QLabel;
        layout->addWidget(
                    new ew::vertical_box( this->_lbl_user,
                                          QObject::tr( "user:" ),
                                          this
                                        )
                         );

        QWidget *w = new QWidget( this );
        w->setLayout( layout );

        return w;
    }

    /// ------------------------------------------------------------------------
    /// init_1st_line( )
    /// ------------------------------------------------------------------------
    QWidget* widget_violation::init_1st_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;

        const int WIDTH_IN_PERCENTS = 25;
        //
        //_txt_regnum
        //
        this->_txt_regnum = new QLineEdit;
        layout->addWidget(
                    new ew::vertical_box( this->_txt_regnum,
                                          QObject::tr( "reg number:" ),
                                          this
                                        ),
                    WIDTH_IN_PERCENTS
                         );
        //
        //_cbx_cam_name
        //
        this->_cbx_cam_name = new combobox_camera_search;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_cam_name,
                                          QObject::tr( "camera name:" ),
                                          this
                                        ),
                    WIDTH_IN_PERCENTS
                         );
        //
        //_lbl_cam_address
        //
        this->_lbl_cam_address = new QLabel( "-" );
        layout->addWidget(
                    new ew::vertical_box( this->_lbl_cam_address,
                                          QObject::tr( "camera address:" ),
                                          this
                                        ),
                    WIDTH_IN_PERCENTS
                         );
        //
        //_cbx_violation_type
        //
        this->_cbx_violation_type = new combobox_violation_type;
        layout->addWidget(
                    new ew::vertical_box( this->_cbx_violation_type,
                                          QObject::tr( "violation type:" ),
                                          this
                                        ),
                    WIDTH_IN_PERCENTS
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
    /// init_4th_line( )
    /// ------------------------------------------------------------------------
    QWidget *widget_violation::init_4th_line( )
    {
        QHBoxLayout *layout = new QHBoxLayout;

        //
        //_txt_note
        //
        this->_txt_note = new QLineEdit;
        layout->addWidget(
                    new ew::vertical_box( this->_txt_note,
                                          QObject::tr( "comment:" ),
                                          this
                                        )
                         );

        //
        //_btn_attachment
        //
        this->_btn_attachment = new QPushButton;
        this->_btn_attachment->setIcon(
                        *( new QIcon( ":/image/images/32x32/mail-attachment.png" ) )
                                 );
        this->_btn_attachment->setToolTip( QObject::tr( "attach file to violation record in DB" ) );
        layout->addWidget( this->_btn_attachment, 0, Qt::AlignBottom|Qt::AlignRight );

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

        this->buttons_mode_default( );

        return widget;
    }

    /// ------------------------------------------------------------------------
    /// extract_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::extract_violation( )
    {
        this->_violation.reg_number( this->_txt_regnum->text( ) );
        this->_violation.violation_type( this->_cbx_violation_type->currentText( ) );
        this->_violation.cam_name( this->_cbx_cam_name->currentText( ) );
        this->_violation.object_type( this->_cbx_object_type->currentText( ) );
        this->_violation.object_name( this->_cbx_object_name->currentText( ) );
        this->_violation.object_id( this->_lbl_id_object->text( ) );
        this->_violation.date_violation( this->_dte_violation->date( ) );
        if( this->_violation.id_violation() == 0 )
        {
            //дата фиксации нарушения ставится только у нового нарушения
            this->_violation.date_record( QDate::currentDate( ) );
        }
        this->_violation.URL( this->_txt_url->text( ) );
        this->_violation.user( application::program_instance( )->user( ) );
        this->_violation.note( this->_txt_note->text( ) );

        const data_violation_object *pvo  = this->_cbx_object_name->violation_object( );
        if( pvo )
        {
            this->_violation.okrug( pvo->okrug( ) );
            this->_violation.prefekture( pvo->prefekture( ) );
            this->_violation.district( pvo->district( ) );
        }
    }

    /// ------------------------------------------------------------------------
    /// fill_controls( const data_violation &v )
    /// ------------------------------------------------------------------------
    void widget_violation::fill_controls( const data_violation &v )
    {
        this->_lbl_user->setText( v.user( ) );
        this->_txt_regnum->setText( v.reg_number( ) );
        this->_cbx_cam_name->camera( v.cam_name( ) );
        this->_cbx_violation_type->violation_type( v.violation_type( ) );
        this->_cbx_object_type->object_type( v.object_type( ) );
        this->_cbx_object_name->refresh( v.object_type( ), v.object_name( ) );
        this->_dte_violation->setDate( v.dt_violation( ) );
        this->_txt_url->setText( v.URL( ) );
        this->_txt_note->setText( v.note( ) );
    }

    /// ------------------------------------------------------------------------
    /// fill_controls( const data_violation &v )
    /// ------------------------------------------------------------------------
    bool widget_violation::data_valid( )
    {
        if( !this->user_valid( ) ) return false;

        if( !this->camera_valid( ) && !this->object_name_valid( ) )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "camera\'s name or object's name field must be filled" )
                                );
            return false;
        }

        return true;
    }

    /// ------------------------------------------------------------------------
    /// camera_valid( )
    /// ------------------------------------------------------------------------
    bool widget_violation::camera_valid( )
    {
        if( this->_cbx_cam_name->currentIndex( ) < 0 )
        {
        /*
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "camera\'s name field must be filled" )
                                );
                                */
            return false;
        }
        return true;
    }

    /// ------------------------------------------------------------------------
    /// object_type_valid( )
    /// ------------------------------------------------------------------------
    bool widget_violation::object_type_valid( )
    {
        QString text_obj_type( this->_cbx_object_type->currentText( ).simplified( ).remove( ' ' ) );
        if( !text_obj_type.length( ) )
        {
        /*
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "object\'s type field must be filled" )
                                );
                                */
            return false;
        }
        return true;
    }

    /// ------------------------------------------------------------------------
    /// object_name_valid( )
    /// ------------------------------------------------------------------------
    bool widget_violation::object_name_valid( )
    {
        if( this->_cbx_object_name->currentIndex( ) < 0 )
        {
        /*
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "object\'s name field must be filled" )
                                );
                                */
            return false;
        }
        return true;
    }

    /// ------------------------------------------------------------------------
    /// URL_valid( )
    /// ------------------------------------------------------------------------
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

    /// ------------------------------------------------------------------------
    /// user_valid( )
    /// ------------------------------------------------------------------------
    bool widget_violation::user_valid( )
    {
        if( application::program_instance( )->user( ).isEmpty( ) )
        {
            QMessageBox::warning(
                                this, tr( "warning" ),
                                tr( "user name must be filled in config file" )
                                );
            return false;
        }
        return true;
    }

    /// ------------------------------------------------------------------------
    /// buttons_mode_default( )
    /// ------------------------------------------------------------------------
    void widget_violation::buttons_mode_default( )
    {
        this->_btn_new->setEnabled( true );
        this->_btn_edit->setEnabled( false );
        this->_btn_save->setEnabled( false );
        this->_btn_clear->setEnabled( false );
        this->_btn_del->setEnabled( false );
    }

    /// ------------------------------------------------------------------------
    /// buttons_mode_view( )
    /// ------------------------------------------------------------------------
    void widget_violation::buttons_mode_view()
    {
        this->_btn_new->setEnabled( true );
        this->_btn_edit->setEnabled( true );
        this->_btn_save->setEnabled( false );
        this->_btn_clear->setEnabled( false );

        const QString &s_group = application::program_instance( )->group( );
        if( s_group.compare( "su" ) == 0 )
        {
            this->_btn_del->setEnabled( true );
        }
        else
        {
            this->_btn_del->setEnabled( false );
        }
    }

    /// ------------------------------------------------------------------------
    /// buttons_mode_edit( )
    /// ------------------------------------------------------------------------
    void widget_violation::buttons_mode_edit()
    {
        this->_btn_new->setEnabled( false );
        this->_btn_edit->setEnabled( false );
        this->_btn_save->setEnabled( true );
        this->_btn_clear->setEnabled( true );
        this->_btn_del->setEnabled( false );
    }

    /// ------------------------------------------------------------------------
    /// controls_disable( )
    /// ------------------------------------------------------------------------
    void widget_violation::controls_disable( )
    {
        //_txt_regnum
        this->_txt_regnum->setEnabled( false );
        //_cbx_cam_name
        this->_cbx_cam_name->setEnabled( false );
        //_lbl_cam_address
        this->_lbl_cam_address->setEnabled( false );
        //_cbx_violation_type
        this->_cbx_violation_type->setEnabled( false );
        //_cbx_object_type
        this->_cbx_object_type->setEnabled( false );
        //_cbx_object_name
        this->_cbx_object_name->setEnabled( false );
        //_lbl_id_object
        this->_lbl_id_object->setEnabled( false );
        //_dte_violation
        this->_dte_violation->setEnabled( false );
        //_txt_url
        this->_txt_url->setEnabled( false );
        //_txt_note
        this->_txt_note->setEnabled( false );
        //_btn_attachment
        this->_btn_attachment->setEnabled( false );
    }

    /// ------------------------------------------------------------------------
    /// controls_enable( )
    /// ------------------------------------------------------------------------
    void widget_violation::controls_enable( )
    {
        //_txt_regnum
        this->_txt_regnum->setEnabled( true );
        //_cbx_cam_name
        this->_cbx_cam_name->setEnabled( true );
        //_lbl_cam_address
        this->_lbl_cam_address->setEnabled( true );
        //_cbx_violation_type
        this->_cbx_violation_type->setEnabled( true );
        //_cbx_object_type
        this->_cbx_object_type->setEnabled( true );
        //_cbx_object_name
        this->_cbx_object_name->setEnabled( true );
        //_lbl_id_object
        this->_lbl_id_object->setEnabled( true );
        //_dte_violation
        this->_dte_violation->setEnabled( true );
        //_txt_url
        this->_txt_url->setEnabled( true );
        //_txt_note
        this->_txt_note->setEnabled( true );
        //_btn_attachment
        this->_btn_attachment->setEnabled( true );
    }

    /// ------------------------------------------------------------------------
    /// controls_clear( )
    /// ------------------------------------------------------------------------
    void widget_violation::controls_clear( )
    {
        //_txt_regnum
        this->_txt_regnum->clear( );
        //_cbx_cam_name
        this->_cbx_cam_name->clear( );
         //_lbl_cam_address
        this->_lbl_cam_address->clear( );
        //_cbx_violation_type
        this->_cbx_violation_type->setCurrentIndex( 0 );
        //_cbx_object_type
        this->_cbx_object_type->setCurrentIndex( 0 );
        //_cbx_object_name
        this->_cbx_object_name->clear( );
        //_lbl_id_object
        this->_lbl_id_object->clear( );
        //_dte_violation
        this->_dte_violation->clear( );
        //_txt_url
        this->_txt_url->clear( );
        //_txt_note
        this->_txt_note->clear( );
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
    /// new_data_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::new_data_violation( )
    {
        this->_violation.clear_data( );

        this->controls_clear( );
        this->controls_enable( );
        this->buttons_mode_edit( );
    }

    /// ------------------------------------------------------------------------
    /// edit_data_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::edit_data_violation( )
    {
        this->controls_enable( );
        this->buttons_mode_edit( );
    }

    /// ------------------------------------------------------------------------
    /// clear_data_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::clear_data_violation( )
    {
        this->controls_disable( );
        this->buttons_mode_default( );
    }

    /// ------------------------------------------------------------------------
    /// delete_data_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::delete_data_violation( )
    {
            //удалить запись
            application::the_business_logic( ).violation_delete( this->_violation );

            this->controls_clear( );
            this->enable_controls( no_selection );
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

        //fill violation object with gui controls' values
        this->extract_violation( );

        if( this->_violation.id_violation( ) == 0 )
        {
            //новая запись
            application::the_business_logic( ).violation_insert( this->_violation );

            this->controls_clear( );
            this->enable_controls( no_selection );
        }
        else
        {
            //редактируемая запись
            application::the_business_logic( ).violation_update( this->_violation );
            this->enable_controls( view_item );
        }
    }

    /// ------------------------------------------------------------------------
    /// enable_controls( )
    /// ------------------------------------------------------------------------
    void widget_violation::enable_controls(widget_violation::widget_violation_mode mode)
    {
        switch( mode )
        {
        case view_item:
            this->buttons_mode_view( );
            this->controls_disable( );
            break;
        case edit_item:
            this->buttons_mode_edit( );
            this->controls_enable( );
            break;

        default:
        case no_selection:
            this->buttons_mode_default( );
            this->controls_disable( );
            break;
        }

    }

    /// ------------------------------------------------------------------------
    /// view_violation( )
    /// ------------------------------------------------------------------------
    void widget_violation::view_violation( const data_violation *v )
    {
        //установить в режим просмотра
        this->buttons_mode_view( );
        //установить элементы управления в режим просмотра
        this->controls_disable( );
        //очистить элементы управления
        this->controls_clear( );
        this->_violation.clear_data( );

        //установить объект просмотра
        if( v )
        {
            this->_violation = *v;
            this->fill_controls( this->_violation );
        }
    }

}//namespace vcamdb
