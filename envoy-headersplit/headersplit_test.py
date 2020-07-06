# Lint as: python3
"""Tests for headersplit."""

import unittest
import headersplit


class HeadersplitTest(unittest.TestCase):

  def test_to_filename(self):
    self.assertEqual(headersplit.to_filename("MockAdminStream"),"admin_stream")



if __name__ == '__main__':
  unittest.main()
