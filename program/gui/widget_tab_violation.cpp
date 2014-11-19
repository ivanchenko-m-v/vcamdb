/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 19-11-2014
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

#include "data_model_violation.h"
#include "data_adapter_violation.h"

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

        this->_lv_violations->setFocus( );
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
        this->connect(
                    this->_lv_violations,
                    SIGNAL( current_violation_changed( const data_violation* ) ),
                    this->_w_violation,
                    SLOT( view_violation( const data_violation* ) )
                     );
        this->connect(
                    this->_lv_violations,
                    SIGNAL( clicked(QModelIndex) ),
                    this,
                    SLOT( view_violation(QModelIndex) )
                     );
                     /*
        this->connect(
                    this->_w_violation,
                    SIGNAL( saved_edited_item( data_violation ) ),
                    this->_lv_violations,
                    SLOT( select_updated_violation( data_violation ) )
                    );
        this->connect(
                    this->_w_violation,
                    SIGNAL( saved_new_item( data_violation ) ),
                    this->_lv_violations,
                    SLOT( clearSelection( ) )
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
    void widget_tab_violation::view_violation( QModelIndex idx )
    {
        if( !idx.isValid( ) )
        {
            return;
        }
        business_logic &logic = application::the_business_logic( );
        const data_violation *v = logic.model_violation( )->violation( idx.row( ) );
        if( v )
        {
            this->_w_violation->view_violation( v );
        }
    }

}//namespace vcamdb
