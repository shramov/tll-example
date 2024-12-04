#!/usr/bin/env python3
# vim: sts=4 sw=4 et

from tll.test_util import Accum

def test(context):
    c = Accum('echo://', context=context)
    c.open()
    assert [(m.seq, m.data.tobytes()) for m in c.result] == []
    c.post(b'xxx', seq=10)
    assert [(m.seq, m.data.tobytes()) for m in c.result] == [(10, b'xxx')]
    c.post(b'zzz', seq=20)
    assert [(m.seq, m.data.tobytes()) for m in c.result] == [(10, b'xxx'), (20, b'zzz')]
