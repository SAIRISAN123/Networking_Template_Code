import asyncio
import websockets

async def handle_connection(connection):
    print("The server is ready to receive")
    async for message in connection:
        capitalized_message = message.upper()
        print(f"Received: {message}")
        # print(f"Sent: {capitalized_message}")
        
        await connection.send(capitalized_message)

async def websocket_server():
    server = await websockets.serve(handle_connection, "localhost", 8765)
    print("WebSocket server is running on ws://localhost:8765")
    await server.wait_closed()

if __name__ == "__main__":
    asyncio.run(websocket_server())
