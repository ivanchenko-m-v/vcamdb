/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 14-10-2014
///		Date update	: 19-10-2014
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_TAB_VIOLATION_H__
#define __WIDGET_TAB_VIOLATION_H__

#include <QWidget>
#include <QModelIndex>

namespace vcamdb
{

class widget_cam_selection;
class listview_cam_selection;
class listview_violation;
class widget_violation;
/// ############################################################################
///			class widget_tab_violation
/// ############################################################################
    class widget_tab_violation : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_tab_violation( const widget_tab_violation &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit widget_tab_violation(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~widget_tab_violation( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        void init_layout();
        void init_connections( );

        QWidget* init_cam_selection_view( );
        QWidget* init_violations_view( );
        /*
        QWidget* init_view_card( );
        QWidget* init_listview_request( );
        QWidget* init_buttons_search( );
        QWidget* init_buttons_listview( );

        void init_stat_menu( );
*/

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
        widget_tab_violation& operator=( const widget_tab_violation &rhs );

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
        void view_violation(QModelIndex idx);

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        widget_cam_selection    *_w_cam_selection;
        listview_cam_selection  *_lv_cams;
        listview_violation      *_lv_violations;
        widget_violation        *_w_violation;

    };//class widget_tab_violation
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __WIDGET_TAB_VIOLATION_H__
