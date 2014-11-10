/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 10-11-2014
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_VIOLATION_H__
#define __WIDGET_VIOLATION_H__

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>

#include "data_adapter_violation.h"

namespace vcamdb
{

class combobox_object_type;
class combobox_camera_search;
class combobox_violation_type;
class combobox_violation_object;

/// ############################################################################
///			class widget_violation
/// ############################################################################
    class widget_violation : public QWidget
    {
    Q_OBJECT
    public:
        enum widget_violation_mode : int
        {
            no_selection = 0,
            view_item = 1,
            edit_item = 2
        };
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_violation( const widget_violation &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit widget_violation( QWidget *parent = 0 );
        /// --------------------------------------------------------------------
        virtual ~widget_violation( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        void init_layout( );
        void init_connections( );

        QWidget* init_1st_line( );
        QWidget* init_2nd_line( );
        QWidget* init_3rd_line( );
        QWidget* init_buttons( );

        /// --------------------------------------------------------------------
        data_violation* extract_violation( );
        void fill_controls( const data_violation &v );
        bool data_valid( );
        bool camera_valid( );
        bool object_type_valid( );
        bool object_name_valid( );
        bool URL_valid( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        const data_violation& violation( ) const
        { return this->_violation; }

        void violation( const data_violation& v )
        {
            this->_violation = v;
            this->fill_controls( v );
        }

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_violation& operator=( const widget_violation &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
	protected:
        virtual void keyPressEvent ( QKeyEvent * event );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:
        /// --------------------------------------------------------------------
        void slot_set_camera_address( int current_cam_index );
        void slot_refresh_violation_object( const QString &text );
        void slot_set_object_id( int );

        void save_data_violation( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        combobox_camera_search      *_cbx_cam_name;
        QLabel                      *_lbl_cam_address;
        combobox_violation_type     *_cbx_violation_type;
        combobox_object_type        *_cbx_object_type;
        combobox_violation_object   *_cbx_object_name;
        QLabel                      *_lbl_id_object;
        QDateEdit                   *_dte_violation;
        QLineEdit                   *_txt_url;

        QPushButton     *_btn_new; //clear all input fields and let it editing
        QPushButton     *_btn_edit;//lets input fields  editing
        QPushButton     *_btn_del; //delete selected violation
        QPushButton     *_btn_clear;//clear editing fields and exit from edit mode
        QPushButton     *_btn_save;//save new and edited violation results

        data_violation _violation;
    };//class widget_violation
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __WIDGET_VIOLATION_H__