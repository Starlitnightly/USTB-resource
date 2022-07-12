//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// createServer
// Creates a server and connects to it locally.
//---------------------------------------------------------------------------------------------
$serverCreated = false;
function createServer(%displayOnMaster)
{
   // Destroy a potentially already created server.
   destroyServer();

   // Make sure the network port is set correctly.
   %failCount = 0;
   %port = $pref::net::port;
   while(%failCount < 10 && !setNetPort(%port))
   {
      echo("Port init failed on port " @ %port @ " trying next port.");
      %port++;
      %failCount++;
   }
   
   allowConnections(true);
   if (%displayOnMaster)
      schedule(0, 0, startHeartbeat);
      
   onServerCreated();
   
   %conn = new GameConnection(ServerConnection);
   %conn.setConnectArgs($pref::Player::name);
   %conn.connectLocal();
   
   $serverConnected = true;
   $serverLocal = true;
   $serverCreated = true;
}

//---------------------------------------------------------------------------------------------
// destroyServer
// Destroys the server.
//---------------------------------------------------------------------------------------------
function destroyServer()
{
   // Can't destroy what isn't created.
   if(!$serverCreated)
      return;
      
   $serverCreated = false;
      
   allowConnections(false);
   stopHeartbeat();

   // Delete all the clients.
   while (ClientGroup.getCount())
   {
      %client = ClientGroup.getObject(0);
      %client.delete();
   }
   
   echo("Destroy Server");
   
   // Clean up.
   purgeResources();
   onServerDestroyed();
}

//---------------------------------------------------------------------------------------------
// onServerInfoQuery
//---------------------------------------------------------------------------------------------
function onServerInfoQuery()
{
   return "Doing OK";
}
