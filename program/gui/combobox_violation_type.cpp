/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 04-11-2014
///		Date update	: 04-11-2014
///		Comment		:
/// ============================================================================
#include "combobox_violation_type.h"

#include "application.h"
#include "business_logic.h"

#include "data_model_violation_type.h"
#include "data_adapter_violation_type.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_violation_type
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_violation_type( )
    /// ------------------------------------------------------------------------
    combobox_violation_type::combobox_violation_type(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_violation_type( )
    /// ------------------------------------------------------------------------
    combobox_violation_type::~combobox_violation_type( )
    {

    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	object_type( )
    /// ------------------------------------------------------------------------
    QString combobox_violation_type::violation_type( )
    {
        if( this->currentIndex( ) == -1 )
        {
            return QString( "" );
        }
        return this->itemData( this->currentIndex( ) ).toString( );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::initialize( )
    {
        data_model_violation_type *model = application::the_business_logic( ).
                                                            model_violation_type( );
        if( !model )
        {
            return;
        }
        const data_violation_type_list& list = model->list( );
        if( !list.size() )
        {
            return;
        }

        this->addItem( "", "" );
        for( int i=0; i<list.size( );++i)
        {
            const data_violation_type *rec = list.at( i );
            this->addItem( rec->violation_type( ), rec->violation_type( ) );
        }
    }

    /// ------------------------------------------------------------------------
    ///	set_violation_type( )
    /// ------------------------------------------------------------------------
    void combobox_violation_type::set_violation_type( const QString &violation_type )
    {
        int index = this->findData( violation_type );
        if( index >= 0 )
        {
            this->setCurrentIndex( index );
        }
    }

}//namespace vcamdb
