/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 04-11-2014
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

namespace vcamdb
{

class combobox_object_type;
class combobox_camera_search;
class combobox_violation_type;

/// ############################################################################
///			class widget_violation
/// ############################################################################
    class widget_violation : public QWidget
    {
    Q_OBJECT
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

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    private:

	public:

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

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        combobox_camera_search  *_cbx_cam_name;
        QLabel                  *_lbl_cam_address;
        combobox_violation_type *_cbx_violation_type;
        combobox_object_type    *_cbx_object_type;
        QComboBox               *_cbx_object_name;
        QLabel                  *_lbl_id_object;
        QDateEdit               *_dte_violation;
        QLineEdit               *_txt_url;

        QPushButton     *_btn_new; //clear all input fields and let it editing
        QPushButton     *_btn_edit;//lets input fields  editing
        QPushButton     *_btn_del; //delete selected violation
        QPushButton     *_btn_save;//save new and edited violation results

    };//class widget_violation
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __WIDGET_VIOLATION_H__
