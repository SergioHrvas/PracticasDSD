#
# Autogenerated by Thrift Compiler (0.16.0)
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#

require 'thrift'

class Fraccion; end

class Fraccion
  include ::Thrift::Struct, ::Thrift::Struct_Union
  NUM = 1
  DEN = 2

  FIELDS = {
    NUM => {:type => ::Thrift::Types::I32, :name => 'num'},
    DEN => {:type => ::Thrift::Types::I32, :name => 'den'}
  }

  def struct_fields; FIELDS; end

  def validate
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field num is unset!') unless @num
    raise ::Thrift::ProtocolException.new(::Thrift::ProtocolException::UNKNOWN, 'Required field den is unset!') unless @den
  end

  ::Thrift::Struct.generate_accessors self
end

