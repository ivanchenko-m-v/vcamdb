/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-02-2015
///		Date update	: 19-02-2015
///		Comment		:
/// ============================================================================
#ifndef __COMBOBOX_RESPONSE_H__
#define __COMBOBOX_RESPONSE_H__

#include <QComboBox>
#include <QKeyEvent>

#include "data_adapter_response.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_response
/// ############################################################################
    class combobox_response : public QComboBox
	{
        Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_response( const combobox_response &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit combobox_response(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~combobox_response( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
        /// --------------------------------------------------------------------
        const data_response* response( );
        /// --------------------------------------------------------------------
        void response(  const data_response *data );

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        void initialize( );
        /// --------------------------------------------------------------------
        void clear_data();

	public:
        /// --------------------------------------------------------------------
        void refresh( const QString &response, const QString &text );

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_response& operator=( const combobox_response &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    protected:
        virtual void keyPressEvent( QKeyEvent * e );

    /// ========================================================================
    ///		SIGNALS
    /// ========================================================================
    signals:
        void response_request( const QString &text );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        data_response_collection _objects;

    };//class combobox_response
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb
#endif // __COMBOBOX_RESPONSE_H__
