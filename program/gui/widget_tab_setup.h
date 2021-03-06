/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 29-12-2014
///		Date update	: 19-02-2015
///		Comment		:
/// ============================================================================
#ifndef __WIDGET_TAB_SETUP_H__
#define __WIDGET_TAB_SETUP_H__

#include <QWidget>
#include <QPushButton>

namespace vcamdb
{

class listview_violation_type;

/// ############################################################################
///			class widget_tab_setup
/// ############################################################################
    class widget_tab_setup : public QWidget
    {
    Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        widget_tab_setup( const widget_tab_setup &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit widget_tab_setup(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~widget_tab_setup( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        void init_layout();
        void init_connections( );

        QWidget* init_buttons( );
        QWidget* init_listview_violation_type( );

        /// --------------------------------------------------------------------
        QString file_select( const QString &caption );



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
        widget_tab_setup& operator=( const widget_tab_setup &rhs );

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
        void slot_import_CA( );
        void slot_import_DT( );
        void slot_import_ODH( );
        void slot_import_contractor( );
        void slot_import_response( );
        void slot_import_violation_type( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QPushButton *_btn_import_DT;
        QPushButton *_btn_import_CA;
        QPushButton *_btn_import_ODH;

        QPushButton *_btn_import_response;
        QPushButton *_btn_import_contractor;
        QPushButton *_btn_import_violation_type;

        listview_violation_type *_lv_violation_type;

    };//class widget_tab_setup
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb

#endif // __WIDGET_TAB_SETUP_H__
