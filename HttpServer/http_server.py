from serverAPI.server_api import ServerAPI
from serverAPI.http_client_handler import HTTPClientHandler
SERVER_RESOURCES = r"C:/ServerResources/webroot"

LISTEN_IP = "0.0.0.0"
LISTEN_PORT = 8080
server = ServerAPI(listen_ip="0.0.0.0", listen_port=8080)
server.start_server(HTTPClientHandler(SERVER_RESOURCES))

