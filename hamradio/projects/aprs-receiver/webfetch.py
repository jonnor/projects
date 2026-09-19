
import asyncio


class AprsISClient:
    """Minimal async APRS-IS TCP client for pulling live packet data.

    Usage:
        async with AprsISClient(callsign="MYCALL1", filter_str="r/40.0/-105.0/500") as client:
            async for line in client.packets():
                print(line)
    """

    def __init__(self, callsign, passcode="-1", host="rotate.aprs2.net",
                 port=14580, filter_str=None, app_name="mytest", app_vers="1.0",
                 timeout=30):
        self.callsign = callsign
        self.passcode = passcode
        self.host = host
        self.port = port
        self.filter_str = filter_str
        self.app_name = app_name
        self.app_vers = app_vers
        self.timeout = timeout

        self._reader = None
        self._writer = None

    async def __aenter__(self):
        self._reader, self._writer = await asyncio.wait_for(
            asyncio.open_connection(self.host, self.port), timeout=self.timeout
        )

        login = f"user {self.callsign} pass {self.passcode} vers {self.app_name} {self.app_vers}"
        if self.filter_str:
            login += f" filter {self.filter_str}"
        login += "\r\n"

        self._writer.write(login.encode("ascii"))
        await self._writer.drain()
        return self

    async def __aexit__(self, exc_type, exc, tb):
        if self._writer:
            self._writer.close()
            try:
                await self._writer.wait_closed()
            except OSError:
                pass
            self._writer = None
            self._reader = None
        return False  # don't suppress exceptions

    async def lines(self):
        """Async generator yielding every raw line, including '#' server lines."""
        if self._reader is None:
            raise RuntimeError("must be used inside 'async with AprsISClient(...) as client:'")

        while True:
            line = await self._reader.readline()
            if not line:
                return  # connection closed by server

            line = line.decode("utf-8", errors="replace").strip()
            if line:
                yield line

    async def packets(self):
        """Async generator yielding only actual APRS packet lines (filters out '#' server lines)."""
        async for line in self.lines():
            if not line.startswith("#"):
                yield line

    async def server_messages(self):
        """Async generator yielding only '#' server status/comment lines."""
        async for line in self.lines():
            if line.startswith("#"):
                yield line


async def main():
    with open("aprs_log.txt", "a") as logfile:
        async with AprsISClient(callsign="MYCALL1", filter_str="r/40.0/-105.0/500") as client:
            async for line in client.packets():
                print(line)
                logfile.write(line + "\n")
                logfile.flush()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        print("\nStopped.")

