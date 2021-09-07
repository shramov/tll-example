#!/usr/bin/env python3
# vim: sts=4 sw=4 et

import tll.channel as C
from tll.config import Config
from tll.error import TLLError
from tll.test_util import Accum

import os
import pytest

@pytest.fixture
def context():
    ctx = C.Context()
    ctx.load(os.path.join(os.environ.get("BUILD_DIR", "build"), "tll-example"), 'channel_module')
    return ctx

def test_example(context):
    c = context.Channel('example://;name=c')
    c.open()
    c.process()
