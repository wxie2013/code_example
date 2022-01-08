import argparse, logger
parser = argparse.ArgumentParser("script1")
logger.add_arguments(parser)
parser.add_argument('-x', '--xtreme')
args = parser.parse_args()
print(args.xtreme, args.verbose)


