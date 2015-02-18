/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 18-02-2015
///		Date update	: 18-02-2015
///		Comment		:
/// ============================================================================
#ifndef __COMBOBOX_CONTRACTOR_H__
#define __COMBOBOX_CONTRACTOR_H__

#include <QComboBox>
#include <QKeyEvent>

#include "data_adapter_contractor.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_contractor
/// ############################################################################
    class combobox_contractor : public QComboBox
	{
        Q_OBJECT
    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_contractor( const combobox_contractor &rhs );

	public:
        /// --------------------------------------------------------------------
        explicit combobox_contractor(QWidget *parent = 0);
        /// --------------------------------------------------------------------
        virtual ~combobox_contractor( );

    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
        /// --------------------------------------------------------------------
        const data_contractor* contractor( );
        /// --------------------------------------------------------------------
        void contractor(  const data_contractor *data );

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
        void refresh( const QString &contractor, const QString &text );

    /// ========================================================================
    ///		OPERATORS
    /// ========================================================================
    private:
        /// --------------------------------------------------------------------
        combobox_contractor& operator=( const combobox_contractor &rhs );

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================
    protected:
        virtual void keyPressEvent( QKeyEvent * e );

    /// ========================================================================
    ///		SIGNALS
    /// ========================================================================
    signals:
        void contractor_request( const QString &text );

    /// ========================================================================
    ///			FIELDS
    /// ========================================================================
    private:
        data_contractor_collection _objects;

    };//class combobox_contractor
/// ############################################################################
/// ----------------------------------------------------------------------------

}//namespace vcamdb
#endif // __COMBOBOX_CONTRACTOR_H__
