#include <iostream>
#include <string>
#include <rfl/yaml.hpp>
#include <rfl/json.hpp>
#include <rfl.hpp>
#include <rfl/Variant.hpp>
#include <rfl/Timestamp.hpp>
#include <rfl/Rename.hpp>
#include <rfl/Processors.hpp>
#include <rfl/Flatten.hpp>
#include <optional>

enum class SrtXTransmitCommand
{
  generate,
  receive,
  route
};

struct StatsConfigFile
{
  std::optional<int>         stats_freq_ms;
  std::optional<std::string> stats_file;
  std::optional<std::string> stats_format;
};

struct ConnConfigFile
{
  std::optional<bool> reconnect;
  std::optional<int>  max_conns;
  std::optional<int>  concurrent_streams;
  std::optional<bool> close_listener; 
};


struct GenerateConfigFile
{
  rfl::Flatten<StatsConfigFile> stats;
  rfl::Flatten<ConnConfigFile> conn;

  std::optional<int>         sendrate;
  std::optional<int>         num_messages;
  std::optional<int>         duration;
  std::optional<int>         message_size; ////8 * 1024 * 1024;
  std::optional<bool>        two_way;
  std::optional<bool>        enable_metrics;
  std::optional<bool>        spin_wait;
  std::optional<std::string> playback_csv;

  std::string outputUrl;
};

struct ReceiveConfigFile
{
  rfl::Flatten<StatsConfigFile> stats;
  rfl::Flatten<ConnConfigFile> conn;

  std::optional<bool>        print_notifications; // Print notifications about the messages received
  std::optional<bool>        send_reply;
  std::optional<bool>        enable_metrics;
  std::optional<unsigned>    metrics_freq_ms;
  std::optional<int>         max_connections; // Maximum number of connections on a socket
  std::optional<int>         message_size;
  std::optional<std::string> metrics_file;

  std::string inputUrl;
};

struct RouteConfigFile
{
  rfl::Flatten<StatsConfigFile> stats;

  std::optional<int> message_size;
  std::optional<bool> bidir;
  std::optional<bool> close_listener;

  std::string outputUrl;
  std::string inputUrl;
};

struct SrtXTransmitConfigFile
{
  SrtXTransmitCommand command;
  std::optional<RouteConfigFile> route;
  std::optional<ReceiveConfigFile> receive;
  std::optional<GenerateConfigFile> generate;
};

template<typename T>
void PrintOptionalField(const std::string name, std::optional<T> val)
{
  if(val.has_value())
  {
    std::cout << name << ": " << val.value() << std::endl; 
  }
}

void PrintGenerateConfig(const GenerateConfigFile& config)
{
  std::cout << "Output url: " << config.outputUrl << std::endl;

  PrintOptionalField("sendrate",            config.sendrate);
  PrintOptionalField("num_messages",        config.num_messages);
  PrintOptionalField("duration",            config.duration);
  PrintOptionalField("message_size",        config.message_size);
  PrintOptionalField("two_way",             config.two_way);
  PrintOptionalField("enable_metrics",      config.enable_metrics);
  PrintOptionalField("spin_wait",           config.spin_wait);
  PrintOptionalField("playback_csv",        config.playback_csv);
  PrintOptionalField("stats_file",          config.stats().stats_file);
  PrintOptionalField("stats_format",        config.stats().stats_format);
  PrintOptionalField("stats_freq_ms",       config.stats().stats_freq_ms);
  PrintOptionalField("reconnect",           config.conn().reconnect);
  PrintOptionalField("max_conns",           config.conn().max_conns);
  PrintOptionalField("concurrent_streams",  config.conn().concurrent_streams);
  PrintOptionalField("close_listener",      config.conn().close_listener);
}

void PrintReceiveConfig(const ReceiveConfigFile& config)
{
  std::cout << "Input url: "  << config.inputUrl  << std::endl;

  PrintOptionalField("print_notifications", config.print_notifications);
  PrintOptionalField("send_reply",          config.send_reply);
  PrintOptionalField("enable_metrics",      config.enable_metrics);
  PrintOptionalField("metrics_freq_ms",     config.metrics_freq_ms);
  PrintOptionalField("max_connections",     config.max_connections);
  PrintOptionalField("message_size",        config.message_size);
  PrintOptionalField("metrics_file",        config.metrics_file);
  PrintOptionalField("stats_file",          config.stats().stats_file);
  PrintOptionalField("stats_format",        config.stats().stats_format);
  PrintOptionalField("stats_freq_ms",       config.stats().stats_freq_ms);
  PrintOptionalField("reconnect",           config.conn().reconnect);
  PrintOptionalField("max_conns",           config.conn().max_conns);
  PrintOptionalField("concurrent_streams",  config.conn().concurrent_streams);
  PrintOptionalField("close_listener",      config.conn().close_listener);
}

void PrintRouteConfig(const RouteConfigFile& config)
{
  std::cout << "Input url: "  << config.inputUrl  << std::endl;
  std::cout << "Output url: " << config.outputUrl << std::endl;

  PrintOptionalField("bidir",           config.bidir);
  PrintOptionalField("close_listener",  config.close_listener);
  PrintOptionalField("message_size",    config.message_size);
  PrintOptionalField("stats_file",      config.stats().stats_file);
  PrintOptionalField("stats_format",    config.stats().stats_format);
  PrintOptionalField("stats_freq_ms",   config.stats().stats_freq_ms);
}

int main()
{
  rfl::Result<SrtXTransmitConfigFile> config = rfl::yaml::load<SrtXTransmitConfigFile>("test_files/config.yaml");

  try
  {
    switch (config.value().command)
    {
      case SrtXTransmitCommand::generate:
      {
        if(config.value().generate.has_value())
        {
          PrintGenerateConfig(config.value().generate.value());
        }
        else
        {
          std::cout << "Error: generate field is empty" << std::endl;
        }

        break;
      }

      case SrtXTransmitCommand::receive:
      {
        if(config.value().receive.has_value())
        {
          PrintReceiveConfig(config.value().receive.value());
        }
        else
        {
          std::cout << "Error: receive field is empty" << std::endl;
        }

        break;
      }

      case SrtXTransmitCommand::route:
      {
        if(config.value().route.has_value())
        {
          PrintRouteConfig(config.value().route.value());
        }
        else
        {
          std::cout << "Error: route field is empty" << std::endl;
        }

        break;
      }
    }
  }
  catch(const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  

  return 0;
}