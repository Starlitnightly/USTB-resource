//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------


/// Player Initialization Procedure
/// 
function onStart()
{   
}

function onExit()
{
}

//---------------------------------------------------------------------------------------------
// Load the paths we need access to
//---------------------------------------------------------------------------------------------
function loadPath( %path )
{
   setModPaths( getModPaths() @ ";" @ %path );
   exec(%path @ "/main.cs");

}

//---------------------------------------------
// Do some bootstrap voodoo to get the game to 
// the initializeProject phase of loading and 
// pass off to the user
//---------------------------------------------

// Output a console log
setLogMode(6);

loadPath( "common" );

loadPath( "game" );

onStart();

// Initialized
echo("\nFunCode (" @ getT2DVersion() @ ") initialized...");

if( !isFunction( "initializeProject" ) || !isFunction( "_initializeProject" ) )
{
   messageBox( "Game Startup Error", "'initializeProject' function could not be found." @
               "\nThis could indicate a bad or corrupt common directory for your game." @
               "\n\nThe Game will now shutdown because it cannot properly function", "Ok", "MIStop" );
   quit();
}

_initializeProject();

// Startup the project
initializeProject();


