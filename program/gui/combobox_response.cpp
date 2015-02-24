/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 19-02-2015
///		Date update	: 24-02-2015
///		Comment		:
/// ============================================================================
#include "combobox_response.h"

#include "application.h"
#include "business_logic.h"

namespace vcamdb
{

/// ############################################################################
///			class combobox_response
/// ############################################################################

    /// ========================================================================
    ///		CONSTRUCTORS/DESTRUCTOR
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	combobox_response( )
    /// ------------------------------------------------------------------------
    combobox_response::combobox_response(QWidget *parent) :
        QComboBox(parent)
    {
        this->initialize( );
    }
    /// ------------------------------------------------------------------------
    ///	~combobox_response( )
    /// ------------------------------------------------------------------------
    combobox_response::~combobox_response( )
    {
    }
    /// ========================================================================
    ///		PROPERTIES
    /// ========================================================================
    /// ------------------------------------------------------------------------
    ///	response( ) set
    /// ------------------------------------------------------------------------
    void combobox_response::response( const QString &s_response )
    {
        int index = this->findText( s_response );
        if( index < 0 )
        {
            this->addItem( s_response );
            index = this->findText( s_response );
        }
        this->setCurrentIndex( index );
    }

    /// ========================================================================
    ///		FUNCTIONS
    /// ========================================================================

    /// ------------------------------------------------------------------------
	///	initialize( )
    /// ------------------------------------------------------------------------
    void combobox_response::initialize( )
    {
        this->setEditable( true );
        //this->setSizeAdjustPolicy( AdjustToContents );
    }

    /// ------------------------------------------------------------------------
    ///	clear_data( )
    /// ------------------------------------------------------------------------
    void combobox_response::clear_data( )
    {
        //empty text list
        this->clear( );
        //remove previous data
        this->_objects.free( );
    }


    /// ------------------------------------------------------------------------
    ///	refresh( )
    /// ------------------------------------------------------------------------
    void combobox_response::refresh(const QString &object_type, const QString &text )
    {
        this->clear( );

        business_logic &logic = application::the_business_logic( );
        data_response_collection *p_coll = logic.response_select( object_type, text );
        if( !p_coll )
        {
            return;
        }

        data_response_collection::iterator it = p_coll->begin( );
        for( ; it < p_coll->end( ); ++it )
        {
            data_response *vobj = *it;

            if( !vobj ) continue;

            this->addItem( vobj->response( ) );
            this->_objects.append( vobj );
        }

        p_coll->free_data_pointer( );
    }

    /// ========================================================================
    ///		EVENTS
    /// ========================================================================

    /// ------------------------------------------------------------------------
    ///	keyPressEvent(QKeyEvent *e)
    /// ------------------------------------------------------------------------
    void combobox_response::keyPressEvent( QKeyEvent *e )
    {
        int n_key = e->key( );
        if(
            n_key != Qt::Key_Enter &&
            n_key != Qt::Key_Return
          )
        {
            QComboBox::keyPressEvent( e );

            return;
        }

        QString text( this->currentText( ).simplified( ).remove( ' ' ) );

        const int MIN_INPUT_LETTERS = 3;
        if( text.length( ) < MIN_INPUT_LETTERS )
        {
            QComboBox::keyPressEvent( e );

            return;
        }

        //Посылаем сигнал для определения типа
        //фиксируемого нарушения
        emit response_request( text );

        QComboBox::keyPressEvent( e );
    }


}//namespace vcamdb
