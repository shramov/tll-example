#!/usr/bin/env python3
# vim: sts=4 sw=4 et

from tll.asynctll import asyncloop_run
from tll.channel.mock import Mock

@asyncloop_run
async def test(asyncloop):
    mock = Mock(asyncloop, f'''yamls://
mock:
  echo: direct://
channel: echo-logic://;tll.channel.echo=echo;name=logic;hello-text=Body;hello-msgid=100
''')

    mock.open(skip=['echo'])
    mock.inner('echo').open()

    ci = mock.io('echo')

    m = await ci.recv()
    assert (m.msgid, m.data.tobytes()) == (100, b'Body')

    ci.post(b'xxx', msgid=10)

    m = await ci.recv()
    assert (m.msgid, m.data.tobytes()) == (10, b'xxx')
