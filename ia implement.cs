using System;
using System.Collections.Generic;

namespace iavl
{
    using CosmosDB = Cosmos.CosmosDB; // Please import the proper namespace for CosmosDB

    public class FastIterator : IEnumerable<KeyValuePair<byte[], byte[]>>
    {
        private byte[] start;
        private byte[] end;
        private bool valid;
        private bool ascending;
        private Exception err;
        private NodeDB ndb;
        private fastnode.Node nextFastNode;
        private IEnumerator<KeyValuePair<byte[], byte[]>> fastIterator;

        public FastIterator(byte[] start, byte[] end, bool ascending, NodeDB ndb)
        {
            this.start = start;
            this.end = end;
            this.err = null;
            this.valid = false;
            this.ascending = ascending;
            this.ndb = ndb;
            this.nextFastNode = null;
            this.fastIterator = null;

            // Move iterator before the first element
            this.MoveNext();
        }

        public byte[] DomainStart
        {
            get
            {
                if (fastIterator == null)
                    return start;

                var (start, end) = fastIterator.Domain();

                if (start != null)
                {
                    start = start[1..];
                    if (start.Length == 0)
                        start = null;
                }

                if (end != null)
                {
                    end = end[1..];
                    if (end.Length == 0)
                        end = null;
                }

                return start;
            }
        }

        public byte[] DomainEnd
        {
            get
            {
                if (fastIterator == null)
                    return end;

                var (start, end) = fastIterator.Domain();

                if (start != null)
                {
                    start = start[1..];
                    if (start.Length == 0)
                        start = null;
                }

                if (end != null)
                {
                    end = end[1..];
                    if (end.Length == 0)
                        end = null;
                }

                return end;
            }
        }

        public bool Valid()
        {
            return fastIterator != null && valid;
        }

        public KeyValuePair<byte[], byte[]> Current
        {
            get
            {
                if (valid)
                    return new KeyValuePair<byte[], byte[]>(nextFastNode.GetKey(), nextFastNode.GetValue());

                return default;
            }
        }

        public void Dispose()
        {
            if (fastIterator != null)
            {
                try
                {
                    fastIterator.Dispose();
                }
                catch (Exception ex)
                {
                    err = ex;
                }
                finally
                {
                    fastIterator = null;
                    valid = false;
                }
            }
        }

        public IEnumerator<KeyValuePair<byte[], byte[]>> GetEnumerator()
        {
            return this;
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return this;
        }

        public bool MoveNext()
        {
            if (ndb == null)
            {
                err = new Exception("fast iterator must be created with a nodedb but it was null");
                valid = false;
                return false;
            }

            if (fastIterator == null)
            {
                var (fastIterator, err) = ndb.getFastIterator(start, end, ascending);
                if (err != null)
                {
                    this.err = err;
                    this.valid = false;
                    return false;
                }

                this.fastIterator = fastIterator.GetEnumerator();
                this.valid = true;
            }
            else
            {
                valid = fastIterator.MoveNext();
            }

            if (err == null)
                err = fastIterator.Error();

            if (valid)
            {
                nextFastNode = fastnode
