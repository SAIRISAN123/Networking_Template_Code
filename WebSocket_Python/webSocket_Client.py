import asyncio
import websockets

async def communicate():
    uri = "ws://localhost:8765" 
    async with websockets.connect(uri) as websocket:
        message = input("Enter a message: ")
        await websocket.send(message)
        # print(f"Sent: {message}")
        
        response = await websocket.recv()
        print(f"Received: {response}")


asyncio.get_event_loop().run_until_complete(communicate())

# # run continlusly chatr application
# while True:
#     asyncio.get_event_loop().run_until_complete(communicate())
