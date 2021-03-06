/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 17-10-2013
///		Date update	: 19-12-2013
///		Comment		:
/// ============================================================================
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#ifndef __DIALOG_ID_REQUEST_H__
#define __DIALOG_ID_REQUEST_H__

#include <QDate>

namespace mac_mediator
{
    class data_request;
/// ############################################################################
///			class dialog_id_request
/// ############################################################################
    class dialog_id_request : public QDialog
	{
	Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        dialog_id_request( const dialog_id_request &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit dialog_id_request( QWidget *parent = 0, Qt::WindowFlags f = 0 );
        /// --------------------------------------------------------------------
        virtual ~dialog_id_request( );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void init_layout( );
        /// --------------------------------------------------------------------
        void init_connections( );
        /// --------------------------------------------------------------------
        QWidget* init_id_lineedit( );
        /// --------------------------------------------------------------------
        QWidget* init_buttons( );
        /// --------------------------------------------------------------------
        void update_id_text( );
        /// --------------------------------------------------------------------
        bool id_valid( int id );

	public:

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
	public:
        /// --------------------------------------------------------------------
        /// request
        data_request* request( )
        {
            return this->_request;
        }
        /// --------------------------------------------------------------------
        /// request
        void request( data_request *r )
        {
            this->_request = r;
            this->update_id_text( );
        }
        /// --------------------------------------------------------------------
        /// id_new
        int id_new( const QDate &dt ) const;

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        dialog_id_request& operator=( const dialog_id_request &rhs );

    /// ========================================================================
    ///		SLOTS
    /// ========================================================================
    private slots:
        void update_request_id( );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        QLabel      *_lbl_ad;
        QLineEdit   *_txt_id;

        QPushButton *_btn_ok;
        QPushButton *_btn_cancel;

        data_request *_request;

	};//class dialog_id_request
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace mac_mediator

#endif // __DIALOG_ID_REQUEST_H__
