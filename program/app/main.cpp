/// $Header
/// ============================================================================
///		Author		: M. Ivanchenko
///		Date create	: 05-10-2014
///		Date update	: 14-10-2014
///		Comment		:
/// ============================================================================
#include "application.h"
#include "main_window.h"

/// ----------------------------------------------------------------------------
///	main( int argc, char *argv[] )
/// ----------------------------------------------------------------------------
int main( int argc, char *argv[] )
{
    vcamdb::application app( argc, argv );

    /*
    app.authorize( );
    if( !app.authorized_mediator( ).mediator( ).length( ) )
    {
        app.exit( -1 );
        return -1;
    }
    */
    vcamdb::main_window w;
    //w.append_title_text( app.authorized_mediator( ).mediator( ) );
    w.show( );

    return app.exec( );
}
