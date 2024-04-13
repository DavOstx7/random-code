from abc import ABC, abstractmethod

class IClientHandler(ABC):
    @abstractmethod
    def handle_client(self, socket_to_client, address):
        pass