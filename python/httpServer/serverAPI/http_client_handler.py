import socket
from serverAPI.server_client_handler import IClientHandler
from typing import List, Dict, Tuple
import os
import time

BUFFER = 1024
POST_SAVEPLACE = b"uploads"
HOME_PAGE = b"index.html"
HTTP_NEWLINE = b"\r\n"
HTTP_METHODS_SUPPORTED = {b"GET", b"POST"}
HTTP_PROTOCOL_SUPPORTED = {b"HTTP/1.1"}
ERROR_MESSAGE = b"HTTP/1.1 404 Not Found" + HTTP_NEWLINE
OK_MESSAGE = b"HTTP/1.1 200 OK" + HTTP_NEWLINE
INTERNAL_ERROR_MESSAGE = b"HTTP/1.1 500 Internal Server Error"
CONTENT_TYPE_TEMPALTE = b"Content-Type: "
TEXT_AND_HTML_CONTENT_TYPE = b"text/html; charset=UTF-8"
IMAGE_CONTENT_TYPE = b"image/jpeg"
JAVASCRIPT_CONTENT_TYPE = b"text/javascript; charset=UTF-8"
CSS_CONTENT_TYPE = b"text/css"
RESOURCE_MAPPER: Dict[bytes, bytes] = {b"html": TEXT_AND_HTML_CONTENT_TYPE, b"txt": TEXT_AND_HTML_CONTENT_TYPE,
                                       b"jpg": IMAGE_CONTENT_TYPE, b"jpeg": IMAGE_CONTENT_TYPE,
                                       b"js": JAVASCRIPT_CONTENT_TYPE,
                                       b"css": CSS_CONTENT_TYPE}


class HTTPClientHandler(IClientHandler):
    def __init__(self, server_resources_root: str) -> None:
        self.server_resources_root = self.__fix_root_path(server_resources_root)

    def __fix_root_path(self, root_path: str) -> bytes:
        root_path = root_path.replace("\\", "/")
        if not root_path.endswith("/"):
            root_path += "/"
        return root_path.encode()

    def smart_join(self, resource) -> bytes:
        if resource == b"index.html":
            return self.server_resources_root + resource
        if b"css" in resource:
            return self.server_resources_root + resource
        if b"jpeg" in resource or b"jpg" in resource:
            return self.server_resources_root + resource
        if b"js" in resource:
            return self.server_resources_root + resource
        if b"imgs" in resource:
            return self.server_resources_root + resource
        return os.path.join(self.server_resources_root.decode(), resource.decode()).encode()

    def __is_valid_resource(self, resource: bytes) -> bool:
        resource_path = self.smart_join(resource)

        if not os.path.exists(resource_path):
            print(f"[-] The server does not not have the specified file resource: {resource.decode()}")
            return False
        if not os.path.isfile(resource_path):
            print(f"[-] The specified resource '{resource.decode()}' is not a file the server can give!")
            return False
        return True

    def _get_content_length_header(self, data: bytes) -> bytes:
        return b"Content-Length: " + str(len(data)).encode() + HTTP_NEWLINE

    def _get_content_type_header(self, resource_requested: bytes) -> bytes:

        if b"." in resource_requested:
            *_, file_type = resource_requested.split(b".")
        else:
            file_type = resource_requested
        if file_type in RESOURCE_MAPPER:
            return CONTENT_TYPE_TEMPALTE + RESOURCE_MAPPER[file_type] + HTTP_NEWLINE
        return b""


    def _get_file_content(self, path_to_file: str) -> bytes:
        full_path = self.smart_join(path_to_file)
        with open(full_path, "rb") as file_handler:
            file_data = file_handler.read()
        return file_data

    def send_error_page(self, socket_to_client: socket.socket) -> None:
        print("[*] Sending error message!")
        html_error_page: bytes = self._get_file_content(b'.error/.error_html.html')
        full_error_message: bytes = ERROR_MESSAGE + self._get_content_type_header(
            b"html") + self._get_content_length_header(
            html_error_page) + HTTP_NEWLINE + html_error_page
        socket_to_client.send(full_error_message)

    def get_http_resource_and_method(self, http_request: bytes) -> Tuple[bytes, bytes]:
        first_line, *_ = http_request.splitlines()
        method, resource, _ = first_line.split()
        if resource == b"/":
            resource = HOME_PAGE
        return method, resource

    def send_resource_to_client(self, socket_to_client: socket.socket, resource: str) -> None:
        resource_data = self._get_file_content(resource)
        full_response = OK_MESSAGE + self._get_content_type_header(resource) + self._get_content_length_header(
            resource_data) + HTTP_NEWLINE + resource_data
        socket_to_client.send(full_response)

    def is_valid_get_request(self, http_request: bytes) -> bool:
        try:
            first_line, *other_lines = http_request.splitlines()
            method, resource, protocol_version = first_line.split()
        except ValueError:
            print(
                f"[-] The POST request does not follow the syntax of GET <resource> {HTTP_PROTOCOL_SUPPORTED}")
            return False
        else:
            if resource == b"/":
                resource = HOME_PAGE
            if not self.__is_valid_resource(resource):
                return False
            if protocol_version not in HTTP_PROTOCOL_SUPPORTED:
                print(
                    f"[-] Invalid HTTP protocol, {protocol_version} is not in supported protocol versions: {HTTP_PROTOCOL_SUPPORTED}")
                return False
            print("[+] Valid HTTP GET request!")
            return True

    def __is_valid_resource_save_place(self, resource_save_place: bytes) -> bool:
        if resource_save_place.count(b"/") != 1:
            print(f"[-] The post request does not save it at a 1 level dir")
            return False
        if b"upload" not in resource_save_place:
            print(f"[-] The post request does not try to save the resource at uploads")
            return False
        return True


    def is_valid_post_request(self, http_request: bytes) -> bool:
        print(http_request)
        try:
            first_line, *other_lines = http_request.splitlines()
            method, resource_save_place, protocol_version = first_line.split()
        except ValueError:
            print(
                f"[-] The POST request does not follow the syntax of POST <resource-place> {HTTP_PROTOCOL_SUPPORTED}")
            return False
        else:
            if not self.__is_valid_resource_save_place(resource_save_place):
                return False
            if protocol_version not in HTTP_PROTOCOL_SUPPORTED:
                print(
                    f"[-] Invalid HTTP protocol, {protocol_version} is not in supported protocol versions: {HTTP_PROTOCOL_SUPPORTED}")
                return False
            print("[+] Valid HTTP POST request!")
            return True

    def handle_get_request(self, socket_to_client: socket.socket, http_request: bytes) -> None:
        if not self.is_valid_get_request(http_request):
            print("Sending GET ERROR")
            self.send_error_page(socket_to_client)
            return
        http_method, http_resource = self.get_http_resource_and_method(http_request)
        self.send_resource_to_client(socket_to_client, http_resource)

    def save_data_from_client(self, socket_to_client, save_place) -> None:
        print(f"* Started writing to {save_place.decode()}")
        with open(self.server_resources_root + save_place, "wb") as file_handler:
            while True:
                data = socket_to_client.recv(BUFFER)
                if len(data) == BUFFER:
                    file_handler.write(data)
                else:
                    file_handler.write(data)
                    break
        print(f"* Finished writing to {save_place.decode()}")


    def get_http_resource_save_place(self, http_request: bytes) -> bytes:

        first_line, *other_lines = http_request.splitlines()
        _, resource_save_place, _ = first_line.split()
        _, resource_name = resource_save_place.split(b"?file-name=")
        return b"uploads/" + resource_name


    def handle_post_request(self, socket_to_client: socket.socket, http_request: bytes):
        if not self.is_valid_post_request(http_request):
            print("Sending POST ERROR")
            self.send_error_page(socket_to_client)
            return
        print("VALID POST REQUEST!")
        resource_save_place = self.get_http_resource_save_place(http_request)
        self.save_data_from_client(socket_to_client, save_place=resource_save_place)

    def send_internal_error(self, socket_to_client: socket.socket) -> None:
        full_internal_error_message = INTERNAL_ERROR_MESSAGE + self._get_content_type_header(b"txt") + self._get_content_length_header(
            "") + HTTP_NEWLINE
        try:
            socket_to_client.send(full_internal_error_message)
        except Exception as e:
            print(e)

    def handle_http_request(self, socket_to_client: socket.socket, address, http_request: bytes) -> None:
        if http_request == b"":
            return
        if b"GET" in http_request:
            print(f"[+] Got GET request from {address}")
            self.handle_get_request(socket_to_client, http_request)
        elif b"POST" in http_request:
            print(f"[+] Got POST request from {address}")
            self.handle_post_request(socket_to_client, http_request)
        else:
            print(f"[-] Got INVALID-METHOD request from {address}")
            print(http_request)
            self.send_internal_error(socket_to_client)

    def handle_client(self, socket_to_client: socket.socket, address) -> None:
        while True:
            http_request = socket_to_client.recv(BUFFER)
            self.handle_http_request(socket_to_client, address, http_request)
